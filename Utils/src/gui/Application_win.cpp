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
                std::cerr << "Error: runThreadWindow called with nullptr window." << std::endl;
                return;
            }

            try {
                if (!window->createWinWindow()) {
                    LOG_ERROR(__logger__, "Failed to create WinAPI window for ID: " + window->getID() + ". Thread will terminate.", r_utils::logger::UNKNOWN_ERROR);
                    return;
                }
                window->show();
            }
            catch (const r_utils::exception::WindowException& e) {
                LOG_ERROR(__logger__, "Exception during WinAPI window creation for ID: " + window->getID() + ": " + e.what(), r_utils::logger::UNKNOWN_ERROR);
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
                // std::lock_guard<std::mutex> lock(__threadsMutex__);
                __threadWindows__[std::this_thread::get_id()] = window;
            }

            while (__running__.load() && GetMessageW(&msg, NULL, 0, 0) > 0) {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
            {
               // std::lock_guard<std::mutex> lock(__threadsMutex__);
                __threadWindows__.erase(std::this_thread::get_id());
            }
            LOG_INFO(__logger__, "Thread for Window '" + window->getID() + "' stopped message loop.");
		}

        void Application::run() {
            if (__running__.exchange(true)) {
                LOG_WARN(__logger__, "Application is already running!");
                return;
            }

            LOG_INFO(__logger__, "Starting Application...");
            __running__ = true;


            {
                //std::lock_guard<std::mutex> lock(__threadsMutex__);
                for (auto const& [id, window] : __windows__) {
                    std::thread threadObj(&Application::runThreadWindow, this, window);
                    __threads__.push_back(std::move(threadObj));
                    LOG_INFO(__logger__, "Thread for Window: '" + id + "' started.");
                }
            }

            while (__running__.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            __running__ = false;
            LOG_INFO(__logger__, "Stopping Application...");
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
            {
                std::lock_guard<std::mutex> lock(__threadsMutex__);
                auto it = __windows__.find(windowID);
                if (it == __windows__.end()) {
                    LOG_ERROR(__logger__, "Error: Window with ID '" + windowID + "' not found for single run.", r_utils::logger::ErrorType::INVALID_INPUT);
                    __running__ = false;
                    return;
                }
                targetWindow = it->second;
            }

            targetWindow->show();

            std::thread threadObj(&Application::runThreadWindow, this, targetWindow);

            {
                std::lock_guard<std::mutex> lock(__threadsMutex__);
                __threads__.push_back(std::move(threadObj));
            }

            LOG_INFO(__logger__, "Thread for Window '" + windowID + "' started.");

            while (__running__.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            LOG_INFO(__logger__, "Stopping Application...");
        }
	} // gui
} // r_utils

#endif // _WIN32