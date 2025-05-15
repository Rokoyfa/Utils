#ifdef _WIN32
#include <windows.h>
#include <string>
#include <codecvt>
#include "gui/Window.h"
#include "exception/gui/WindowException.h"

namespace r_utils
{
	namespace gui
	{
		Window::Window(std::string id, const std::string& title, int width, int height, bool expandable)
			: __id__(id), __title__(title), __width__(width), __height__(height), __isExpandable__(expandable), __isVisible__(true), __hwnd__(nullptr) 
		{
			const wchar_t CLASS_NAME[] = L"RUtilsWindowsClass";
			HINSTANCE hInstance = GetModuleHandle(nullptr);


			std::wstring wIconPath;
			int wIconPathLength = MultiByteToWideChar(CP_UTF8, 0, __iconPath__.c_str(), -1, nullptr, 0);
			if (wIconPathLength > 0) {
				wIconPath.resize(wIconPathLength);
				MultiByteToWideChar(CP_UTF8, 0, __iconPath__.c_str(), -1, &wIconPath[0], wIconPathLength);
				wIconPath.resize(wIconPathLength - 1);
			}
			else
			{
				DWORD error = GetLastError();
				std::cerr << "MultiByteToWideChar failed: " << error << std::endl;
				wIconPath = L"Icon.ico";
			}
			HICON hIcon = static_cast<HICON>(LoadImageW(
				hInstance,
				wIconPath.c_str(),
				IMAGE_ICON,
				32,
				32,
				LR_LOADFROMFILE | LR_DEFAULTSIZE
			));

			WNDCLASS wc = {};
			wc.lpfnWndProc = DefWindowProc;
			wc.hInstance = hInstance;
			wc.hIcon = hIcon;
			wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wc.lpszClassName = CLASS_NAME;
			
			if (!RegisterClass(&wc)) {
				throw r_utils::exception::WindowException("Error register the Window-Class!");
			}

			__hwnd__ = CreateWindowExW(
				0,												  // Optional window styles.
				CLASS_NAME,										  // Window class
				std::wstring(title.begin(), title.end()).c_str(), // Window text
				WS_OVERLAPPEDWINDOW,							  // Window style

																  // Size and position
				CW_USEDEFAULT, CW_USEDEFAULT, width, height,

				nullptr,										  // Parent window    
				nullptr,										  // Menu
				hInstance,										  // Instance handle
				nullptr											  // Pointer to window creation data 
			);

			if (!__hwnd__) {
				throw r_utils::exception::WindowException("Error Creating a Windows Window!");
			}

			HICON hIconSm = static_cast<HICON>(LoadImageW(
				hInstance,
				wIconPath.c_str(),
				IMAGE_ICON,
				16,
				16,
				LR_LOADFROMFILE | LR_DEFAULTSIZE
			));
			if (hIconSm) {
				SendMessageW(__hwnd__, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIconSm));
			}
			if (hIcon)
			{
				SendMessageW(__hwnd__, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon));
			}
		}

		Window::~Window()
		{
			if (__hwnd__) {
				DestroyWindow(__hwnd__);
				__hwnd__ = nullptr;
			}
		}

		void Window::updateWindow(MSG msg)
		{
			while (PeekMessageA(&msg, getHWND(), 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		void Window::show() 
		{
			if (!__hwnd__) {
				throw r_utils::exception::WindowException("HWND is not Given or NULL!");
			}
			ShowWindow(static_cast<HWND>(__hwnd__), SW_SHOW);
			__isVisible__ = true;
		}

		void Window::hide() 
		{
			if (!__hwnd__) {
				throw r_utils::exception::WindowException("HWND is not Given or NULL!");
			}
			ShowWindow(static_cast<HWND>(__hwnd__), SW_HIDE);
			__isVisible__ = false;
		}

		void Window::close()
		{
			if (!__hwnd__)
			{
				throw r_utils::exception::WindowException("HWND is not Given or NULL!");
			}
			CloseWindow(__hwnd__);
		}

		const HWND& Window::getHWND() const {
			return __hwnd__;
		}
	}
}
#endif