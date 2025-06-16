#ifdef _WIN32
#include <windows.h>

#include "gui/Application.h"
#include "gui/Window.h"
#include "exception/gui/WindowException.h"
#include "exception/gui/WindowApplicationException.h"
#include "logger/LoggerMakro.h"

#include <iostream>

namespace r_utils
{
	namespace gui
	{

		void Application::runThreadWindow(r_utils::gui::Window* window)
		{
            if (!window) {
                LOG_ERROR(__logger__, "Error: runThreadWindow called with nullptr window.", r_utils::logger::ErrorType::NULL_POINTER_DEREFERENCE);
                return;
            }

            try {
                if (!window->createWinWindow()) {
                    LOG_ERROR(__logger__, "Failed to create WinAPI window for ID: " + window->getID() + ". Thread will terminate.", r_utils::logger::RUNTIME_ERROR);
                    return;
                }
                window->show();
            }
            catch (const r_utils::exception::WindowException& e) {
                LOG_ERROR(__logger__, "Exception during WinAPI window creation for ID: " + window->getID() + ": " + e.what(), r_utils::logger::RUNTIME_ERROR);
                return;
            }
            catch (const std::exception& e) {
                LOG_ERROR(__logger__, "Unknown Exception during WinAPI window creation for ID: " + window->getID() + ": " + e.what(), r_utils::logger::UNKNOWN_ERROR);
                return;
            }

            MSG msg = {};

            LOG_INFO(__logger__, "Thread for window '" + window->getID() + "'.");
            std::ostringstream thread_id_stream;
            thread_id_stream << std::this_thread::get_id();
            LOG_INFO(__logger__, "Starting in thread : " + thread_id_stream.str());

            {
                std::lock_guard<std::mutex> lock(__threadsMutex__);
                __threadWindows__[std::this_thread::get_id()] = window;
            }

            while (__running__.load() && GetMessageW(&msg, NULL, 0, 0) > 0) {
                try
                {
                    if (msg.message == WM_USER + 1) {
                        HWND targetHwnd = reinterpret_cast<HWND>(msg.lParam);
                        if (targetHwnd) {
                            DestroyWindow(targetHwnd);
                        }
                        continue;
                    }

                    TranslateMessage(&msg);
                    DispatchMessageW(&msg);
                }
                catch (const r_utils::exception::WindowApplicationException& e)
                {
                    LOG_ERROR(__logger__, "Exception in message processing for windows '" + window->getID() + "': " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
                }

            }

            {
                __threadWindows__.erase(std::this_thread::get_id());
            }
		}

        void Application::run() {
            if (__running__.exchange(true)) {
                LOG_WARN(__logger__, "Application is already running!");
                return;
            }

            LOG_DEBUG(__logger__, "Starting Application...");
            __running__ = true;


            {
                std::lock_guard<std::mutex> lock(__threadsMutex__);
                for (auto const& [id, window] : __windows__) {
                    try {
                        std::thread threadObj(&Application::runThreadWindow, this, window);
                        __threads__.push_back(std::move(threadObj));
                        LOG_INFO(__logger__, "Thread for window: '" + id + "' started.");
                    }
                    catch (const std::system_error& e) {
                        LOG_ERROR(__logger__, "Error when starting the threads for windows '" + id + "': " + e.what(), r_utils::logger::ErrorType::RUNTIME_ERROR);
                    }
                    catch (const std::exception& e) {
                        LOG_ERROR(__logger__, "Unknown exception when starting the thread for windows '" + id + "': " + e.what(), r_utils::logger::ErrorType::RUNTIME_ERROR);
                    }
                }
            }

            while (__running__.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            std::vector<std::string> windowIDsToClose;
            try {
                std::lock_guard<std::mutex> lock(__threadsMutex__);
                for (const auto& pair : __windows__) {
                    windowIDsToClose.push_back(pair.first);
                }
            }
            catch (const r_utils::exception::WindowApplicationException& e) {
                LOG_ERROR(__logger__, "Exception when creating the list of windows to be closed: " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
            }

            for (const std::string& id : windowIDsToClose) {
                try {
                    removeWindow(id);
                }
                catch (const r_utils::exception::WindowApplicationException& e) {
                    LOG_ERROR(__logger__, "Error when removing the window during shutdown: " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
                }
                catch (const std::exception& e) {
                    LOG_ERROR(__logger__, "Unknown exception when removing the window during shutdown: " + std::string(e.what()), r_utils::logger::ErrorType::UNKNOWN_ERROR);
                }
            }

            std::vector<std::thread> threadsToJoin;
            try {
                std::lock_guard<std::mutex> lock(__threadsMutex__);
                for (auto& thread : __threads__) {
                    if (thread.joinable()) {
                        threadsToJoin.push_back(std::move(thread));
                    }
                }
                __threads__.clear();
            }
            catch (const r_utils::exception::WindowApplicationException& e) {
                LOG_ERROR(__logger__, "Exception when preparing threads for joining: " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
            }

            for (auto& thread : threadsToJoin) {
                try {
                    LOG_INFO(__logger__, "Join window thread during shutdown.");
                    thread.join();
                }
                catch (const r_utils::exception::WindowApplicationException& e) {
                    LOG_ERROR(__logger__, "Exception when joining a thread during shutdown: " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
                }
            }
        }

        void Application::run(std::string& windowID)
        {
            if (__running__.exchange(true)) {
                LOG_WARN(__logger__, "Application is already running (single window run requested)!");
                return;
            }

            LOG_INFO(__logger__, "Starting Application with Window: '" + windowID + "'");

            __running__ = true;
            Window* targetWindow = nullptr;

            try {
                std::lock_guard<std::mutex> lock(__threadsMutex__);
                auto it = __windows__.find(windowID);
                if (it == __windows__.end()) {
                    LOG_ERROR(__logger__, "Error: Window with ID '" + windowID + "' not found for single run.", r_utils::logger::ErrorType::INVALID_INPUT);
                    __running__ = false;
                    return;
                }
                targetWindow = it->second;
            }
            catch (const std::exception & e)
            {
                LOG_ERROR(__logger__, "Exception when calling up the target window for individual runs: " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
                __running__ = false;
                return;
            }

            try {
                std::thread threadObj(&Application::runThreadWindow, this, targetWindow);
                {
                    std::lock_guard<std::mutex> lock(__threadsMutex__);
                    __threads__.push_back(std::move(threadObj));
                }
                LOG_DEBUG(__logger__, "Thread for window '" + windowID + "' satrted.");
            }
            catch (const std::system_error& e) {
                LOG_ERROR(__logger__, "Error when starting the thread for windows '" + windowID + "': " + e.what(), r_utils::logger::ErrorType::RUNTIME_ERROR);
                __running__ = false;
                return;
            }
            catch (const std::exception& e) {
                LOG_ERROR(__logger__, "Unknown exception when starting the thread for windows '" + windowID + "': " + e.what(), r_utils::logger::ErrorType::UNKNOWN_ERROR);
                __running__ = false;
                return;
            }

            while (__running__.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            LOG_DEBUG(__logger__, "Stopping Application...");
        }
	} // gui
} // r_utils

#endif // _WIN32