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
		}

		Application::~Application() {
			LOG_DEBUG(__logger__, "Destructing Application!");
			__dispatcher__.removeListener(this);

			LOG_DEBUG(__logger__, "1");
			{
				std::lock_guard<std::mutex> lock(__threadsMutex__);
				for (auto& thread : __threads__) {
					if (thread.joinable()) {
						thread.join();
					}
				}
				__threads__.clear();
			}
			LOG_DEBUG(__logger__, "2");
			for (auto const& [id, window] : __windows__) {
				delete window;
			}
			LOG_DEBUG(__logger__, "3");
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
			LOG_INFO(__logger__, "Window: '" + window->getID() + "' registered.");
		}

		void Application::removeWindow(r_utils::gui::Window* window)
		{
			removeWindow(window->getID());
		}

		void Application::removeWindow(std::string windowID)
		{
			auto it = __windows__.find(windowID);
			if (it == __windows__.end())
			{
				LOG_ERROR(__logger__, "Error: Window with ID '" + windowID + "' does not exist! Cannot remove.", r_utils::logger::ErrorType::UNKNOWN_ERROR);
				return;
			}

			r_utils::gui::Window* rmWindow = it->second;
			/*
			if (rmWindow && rmWindow->getHWND()) {
				if (rmWindow->getWinThreadId() != 0)
				{
					PostThreadMessage(rmWindow->getWinThreadId(), WM_USER + 1, 0, reinterpret_cast<LPARAM>(rmWindow->getHWND()));
				}
				else
				{
					DestroyWindow(rmWindow->getHWND());
				}

				__dispatcher__.removeListener(this);
			}
			*/
			__dispatcher__.removeListener(rmWindow);
		}


		std::vector<r_utils::gui::Window*> Application::getWindows() const
		{
			std::vector<r_utils::gui::Window*> windows;

			for (auto& [key, value] : __windows__)
			{
				windows.push_back(value);
			}

			return windows;
		}

		r_utils::gui::Window* Application::getWindow(r_utils::gui::Window& window) const
		{
			return getWindow(window.getID());
		}

		r_utils::gui::Window* Application::getWindow(std::string windowID) const
		{
			auto it = __windows__.find(windowID);
			if (it == __windows__.end())
			{
				LOG_WARN(__logger__, "Window with ID '" + windowID + "' not found.");
				return nullptr;
			}

			return const_cast<Window*>(it->second);
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
			/*
			case r_utils::events::EventType::WINDOW_CLOSE:
			{
				r_utils::gui::events::WindowCloseEvent& closeEvent = static_cast<r_utils::gui::events::WindowCloseEvent&>(event);
				removeWindow(closeEvent.getId());
				event.setHandled(true);
				break;
			}
			*/
			default:
				break;
			}
		}

		void Application::stop()
		{
			if (__running__.load()) {
				r_utils::gui::events::AppQuitEvent qevent;
				__dispatcher__.dispatch(qevent);
				__running__ = false;
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
