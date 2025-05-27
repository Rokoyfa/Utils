#ifdef _WIN32
#include <windows.h>
#include <string>
#include <iostream>
#include <codecvt>
#include <locale> 
#include <thread>
#include <sstream>

#include "gui/Window.h"
#include "exception/gui/WindowException.h"
#include <logger/LoggerMakro.h>

namespace r_utils
{
    namespace gui
    {
        std::unordered_map<HWND, Window*> Window::__windowMap__;

        Window::Window(std::string id, const std::string& title, int width, int height, r_utils::logger::Logger* logger)
            : __id__(id), __title__(title), __width__(width), __height__(height), __isVisible__(true), __hwnd__(nullptr), __logger__(logger)
        {
            LOG_INFO(__logger__, "Window Object created for ID: " + __id__);
        }

        Window::Window(std::string id, const std::string& title, r_utils::logger::Logger* logger)
            : __id__(id), __title__(title), __width__(600), __height__(800), __isVisible__(true), __hwnd__(nullptr), __logger__(logger)
        {
            LOG_INFO(__logger__, "Window Object created for ID: " + __id__);
        }

        Window::~Window()
        {
            if (__hwnd__) {
                auto it = Window::__windowMap__.find(__hwnd__);
                if (it != Window::__windowMap__.end()) {
                    Window::__windowMap__.erase(it);
                }

                DestroyWindow(__hwnd__);
            }
        }

        bool Window::createWinWindow()
        {
            const wchar_t CLASS_NAME[] = L"RUtilsWindowsClass";
            HINSTANCE hInstance = GetModuleHandle(nullptr);

            std::wstring wIconPath;
            int num_chars_icon = MultiByteToWideChar(CP_UTF8, 0, __iconPath__.c_str(), -1, nullptr, 0);
            if (num_chars_icon > 0) {
                wIconPath.resize(num_chars_icon - 1);
                MultiByteToWideChar(CP_UTF8, 0, __iconPath__.c_str(), -1, &wIconPath[0], num_chars_icon);
            }
            else {
                DWORD error = GetLastError();

                std::stringstream errorMessage;
                errorMessage << "Failed to convert icon path '"
                    << __iconPath__.c_str()
                    << "' to wide char: "
                    << std::to_string(error);

                LOG_ERROR(__logger__, errorMessage.str(), r_utils::logger::ErrorType::INVALID_INPUT);
                wIconPath = L"Icon.ico"; // Fallback
            }

            HICON hIcon = static_cast<HICON>(LoadImageW(
                hInstance,
                wIconPath.c_str(),
                IMAGE_ICON,
                32,
                32,
                LR_LOADFROMFILE | LR_DEFAULTSIZE
            ));
            if (!hIcon && GetLastError() != 0) {
                DWORD error = GetLastError();
                std::stringstream errorMessage;
                errorMessage << "LoadImageW for icon '" 
                    << __iconPath__ 
                    << "' failed: " 
                    << error;

                LOG_ERROR(__logger__, errorMessage.str(), r_utils::logger::ErrorType::INVALID_INPUT);
            }


            WNDCLASS wc = {};
            wc.lpfnWndProc = Window::WindowProc;
            wc.hInstance = hInstance;
            wc.hIcon = hIcon;
            wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
            wc.lpszClassName = CLASS_NAME;
            wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

            std::string s_CLASS_NAME;
            int len = WideCharToMultiByte(CP_UTF8, 0, CLASS_NAME, -1, nullptr, 0, nullptr, nullptr);
            if (len > 0) {
                s_CLASS_NAME.resize(len - 1);
                WideCharToMultiByte(CP_UTF8, 0, CLASS_NAME, -1, &s_CLASS_NAME[0], len, nullptr, nullptr);
            }

            if (!GetClassInfoW(hInstance, CLASS_NAME, &wc))
            {
                LOG_INFO(__logger__, "Registering window class '" + s_CLASS_NAME + "'.");
                if (!RegisterClassW(&wc)) {
                    DWORD error = GetLastError();

                    std::stringstream errorMessage;
                    errorMessage << "Error registering the Window-Class! GetLastError: "
                        << error;
                    LOG_ERROR(__logger__, errorMessage.str(), r_utils::logger::ErrorType::UNKNOWN_ERROR);

                    return false;
                }
            }

            std::wstring wTitle;
            int num_chars_title = MultiByteToWideChar(CP_UTF8, 0, __title__.c_str(), -1, nullptr, 0);
            if (num_chars_title > 0) {
                wTitle.resize(num_chars_title - 1);
                MultiByteToWideChar(CP_UTF8, 0, __title__.c_str(), -1, &wTitle[0], num_chars_title);
            }
            else {
                wTitle = L"Default Window";
            }

            __hwnd__ = CreateWindowExW(
                0,                                      // Optional window styles.
                CLASS_NAME,                             // Window class
                wTitle.c_str(),                         // Window text
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,       // Window style (WS_VISIBLE hinzugefügt, da show() später aufgerufen wird)

                // Size and position
                CW_USEDEFAULT, CW_USEDEFAULT, __width__, __height__,

                nullptr,                                // Parent window
                nullptr,                                // Menu
                hInstance,                              // Instance handle
                this                                    // Pointer to window creation data (für WM_NCCREATE)
            );

            if (!__hwnd__) {
                DWORD error = GetLastError();

                std::stringstream errorMessage;
                errorMessage << "Error Creating a Windows Window for ID '"
                    << __id__
                    << "'! GetLastError: "
                    << error;
                LOG_ERROR(__logger__, errorMessage.str(), r_utils::logger::ErrorType::UNKNOWN_ERROR);

                return false;
            }
            std::stringstream logMessage;
            logMessage << "Window HWND created: "
                << static_cast<void*>(__hwnd__)
                << " for ID: "
                << __id__
                << " in thread: "
                << std::this_thread::get_id();

            LOG_INFO(__logger__, logMessage.str());

            HICON hIconSm = static_cast<HICON>(LoadImageW(
                hInstance, wIconPath.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE | LR_DEFAULTSIZE
            ));
            if (hIconSm) {
                SendMessageW(__hwnd__, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIconSm));
            }
            if (hIcon) {
                SendMessageW(__hwnd__, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon));
            }
            __isVisible__ = true;

            return true;
        }

        void Window::updateWindow(MSG& msg)
        {
            while (PeekMessageW(&msg, getHWND(), 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
        }

        void Window::show()
        {
            if (!__hwnd__) {
                throw r_utils::exception::WindowException("HWND is not Given or NULL!");
            }
            ShowWindow(static_cast<HWND>(__hwnd__), SW_SHOW);
            UpdateWindow(static_cast<HWND>(__hwnd__));
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
            SendMessage(__hwnd__, WM_CLOSE, 0, 0);
        }

        const HWND& Window::getHWND() const {
            return __hwnd__;
        }

        LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            Window* pWindow = nullptr;
            if (uMsg == WM_NCCREATE) {
                CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
                pWindow = reinterpret_cast<Window*>(pCreate->lpCreateParams);
                SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow)); // SetWindowLongPtrW
            }
            else {
                pWindow = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA)); // GetWindowLongPtrW
            }

            if (pWindow) {
                switch (uMsg) {
                case WM_CLOSE:
                {
                    DestroyWindow(hwnd);
                    auto it = Window::__windowMap__.find(hwnd);
                    if (it != Window::__windowMap__.end()) {
                        Window::__windowMap__.erase(it);
                    }
                    return 0;
                }
                case WM_DESTROY:
                {
                    return 0;
                }
                case WM_SIZE:
                {
                    int newWidth = LOWORD(lParam);
                    int newHeight = HIWORD(lParam);

                    pWindow->__width__ = newWidth;
                    pWindow->__height__ = newHeight;

                    InvalidateRect(hwnd, nullptr, TRUE);
                    return 0; 
                }
                case WM_PAINT:
                {
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hwnd, &ps);
                    pWindow->draw();
                    EndPaint(hwnd, &ps);
                    return 0;
                }
                }
            }

            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
        }
    } // gui
} // r_utils
#endif // _WIN32