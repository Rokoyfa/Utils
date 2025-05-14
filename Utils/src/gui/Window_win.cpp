#ifdef _WIN32
#include <windows.h>
#include "gui/Window.h"
#include "exception/gui/WindowException.h"

namespace r_utils
{
	namespace gui
	{
		Window::Window(const std::string& title, int width, int height, bool expandable)
			: __title__(title), __width__(width), __height__(height), __isExpandable__(expandable), __isVisible__(true), __hwnd__(nullptr) 
		{
			const wchar_t CLASS_NAME[] = L"RUtilsWindowsClass";

			WNDCLASS wc = {};
			wc.lpfnWndProc = DefWindowProc;
			wc.hInstance = GetModuleHandle(nullptr);
			wc.lpszClassName = CLASS_NAME;
			RegisterClass(&wc);

			__hwnd__ = CreateWindowExW(
				0,                              // Optional window styles.
				CLASS_NAME,                     // Window class
				std::wstring(title.begin(), title.end()).c_str(), // Window text
				WS_OVERLAPPEDWINDOW,            // Window style

				// Size and position
				CW_USEDEFAULT, CW_USEDEFAULT, width, height,

				nullptr,                        // Parent window    
				nullptr,                        // Menu
				GetModuleHandle(nullptr),       // Instance handle
				nullptr                         // Pointer to window creation data 
			);

			if (!__hwnd__) {
				throw r_utils::exception::WindowException("Error Creating a Windows Window!");
			}
		}

		Window::~Window()
		{
			if (__hwnd__) {
				DestroyWindow(__hwnd__);
				__hwnd__ = nullptr;
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