#include "gui/Application.h"
#include "exception/gui/WindowApplicationException.h"
#include "logger/LoggerMakro.h"

namespace r_utils
{
	namespace gui
	{
		r_utils::gui::Application::Application(r_utils::logger::Logger* logger)
			: __logger__(logger), __running__(false)
		{
			LOG_DEBUG(__logger__, "Initialized Application!");
			__dispatcher__.addListener(this);
		}

		Application::~Application() {
			LOG_DEBUG(__logger__, "Destructing Application!");
			__dispatcher__.removeListener(this);

			try {
				std::lock_guard<std::mutex> lock(__threadsMutex__);
				for (auto& thread : __threads__) {
					if (thread.joinable()) {
						thread.join();
					}
				}
				__threads__.clear();
			}
			catch (const std::exception& e)
			{
				LOG_ERROR(__logger__, "Exception when preparing threads for joining in the destructor: " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
			}

			for (auto const& [id, window] : __windows__) {
				if (window)
				{
					try
					{
						removeWindow(window);
					} 
					catch (const std::exception& e)
					{
						LOG_ERROR(__logger__, "Exception when removing a window object in the destructor: " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
					}
				}
			}

			__windows__.clear();
			__threadWindows__.clear();
		}


		void Application::registerWindow(r_utils::gui::Window* window)
		{
			
			std::lock_guard<std::mutex> lock(__threadsMutex__);
			if (exists(window->getID()))
			{
				LOG_ERROR(__logger__, "Error: Window with ID '" + window->getID() + "' already exists! Cannot register.", r_utils::logger::ErrorType::INVALID_INPUT);
				return;
			}

			__windows__[window->getID()] = window;
			__dispatcher__.addListener(window);
		}

		void Application::removeWindow(r_utils::gui::Window* window)
		{
			removeWindow(window->getID());
		}

		void Application::removeWindow(std::string windowID)
		{
			try
			{
				std::lock_guard<std::mutex> lock(__threadsMutex__);
				auto it = __windows__.find(windowID);
				if (it == __windows__.end())
				{
					LOG_ERROR(__logger__, "Error: Window with ID '" + windowID + "' does not exist! Cannot remove.", r_utils::logger::ErrorType::INVALID_INPUT);
					return;
				}

				r_utils::gui::Window* rmWindow = it->second;
				__windows__.erase(it);

				if (rmWindow) {
					PostThreadMessage(rmWindow->getWinThreadId(), WM_USER + 1, 0, reinterpret_cast<LPARAM>(rmWindow->getHWND()));
				}
				__dispatcher__.removeListener(rmWindow);
				delete rmWindow;
			} 
			catch (std::exception& e)
			{
				LOG_ERROR(__logger__, "Exception when removing the window: " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
				throw r_utils::exception::WindowApplicationException("[Application]" + std::string(e.what()));
			}
		}


		std::vector<r_utils::gui::Window*> Application::getWindows() const
		{
			std::vector<r_utils::gui::Window*> windows;

			try {
				for (auto& [key, value] : __windows__)
				{
					windows.push_back(value);
				}
			}
			catch (const std::exception& e) {
				LOG_ERROR(__logger__, "Exception returning the window list: " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
			}

			return windows;
		}

		r_utils::gui::Window* Application::getWindow(r_utils::gui::Window& window) const
		{
			if (!window.getID().empty()) {
				return getWindow(window.getID());
			}
			else {
				LOG_WARN(__logger__, "Window ID is empty when retrieving the window via object.");
				return nullptr;
			}
		}

		r_utils::gui::Window* Application::getWindow(std::string windowID) const
		{
			try {
				auto it = __windows__.find(windowID);
				if (it == __windows__.end())
				{
					LOG_WARN(__logger__, "Window with ID '" + windowID + "' not found.");
					return nullptr;
				}
				return const_cast<Window*>(it->second);
			}
			catch (const std::exception& e) {
				LOG_ERROR(__logger__, "Exception when retrieving the window by ID: " + std::string(e.what()), r_utils::logger::ErrorType::RUNTIME_ERROR);
				return nullptr;
			}
		}


		void Application::onEvent(r_utils::events::Event& event)
		{
			switch (event.getType()) {
			case r_utils::events::EventType::APP_QUIT:
			{
				__running__ = false;
				event.setHandled(true);
				break;
			}
			case r_utils::events::EventType::WINDOW_CLOSE:
			{
				r_utils::gui::events::WindowCloseEvent& closeEvent = static_cast<r_utils::gui::events::WindowCloseEvent&>(event);
				removeWindow(closeEvent.getWindow());
				event.setHandled(true);
				break;
			}
			default:
				break;
			}
		}

		void Application::stop()
		{
			if (__running__.load()) {
				r_utils::gui::events::AppQuitEvent qevent;
				__dispatcher__.dispatch(qevent);
			}
		}

		r_utils::events::EventDispatcher& Application::getEventDispatcher()
		{
			return __dispatcher__;
		}


		bool Application::exists(r_utils::gui::Window* window) const
		{
			if (!window) { return false; }
			return __windows__.count(window->getID()) > 0;
		}

		bool Application::exists(std::string windowID) const
		{
			return __windows__.count(windowID) > 0;
		}

	} // gui
} // r_utils
