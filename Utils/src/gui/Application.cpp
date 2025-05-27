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
			__running__ = false;
			{
				std::lock_guard<std::mutex> lock(__threadsMutex__);
				for (auto& thread : __threads__) {
					if (thread.joinable()) {
						thread.join();
					}
				}
			}
			for (auto const& [id, window] : __windows__) {
				delete window;
			}
			__windows__.clear();
			__threadWindows__.clear();
		}


		void Application::registerWindow(r_utils::gui::Window* window)
		{
			if (exists(window->getID()))
			{
				LOG_ERROR(__logger__, "Error: Window with ID '" + window->getID() + "' already exists! Cannot register.", r_utils::logger::ErrorType::INVALID_INPUT);
				return;
			}

			__windows__[window->getID()] = window;
			LOG_INFO(__logger__, "Window '" + window->getID() + "' successfully registered.");
		}

		void Application::removeWindow(r_utils::gui::Window* window)
		{
			removeWindow(window->getID());
		}

		void Application::removeWindow(std::string windowID)
		{
			if (!exists(windowID))
			{
				LOG_ERROR(__logger__, "Error: Window with ID '" + windowID + "' does not exist! Cannot remove.", r_utils::logger::ErrorType::FILE_NOT_FOUND);
				throw r_utils::exception::WindowApplicationException("Error: Window with ID '" + windowID + "' does not exist!");
			}

			auto it = __windows__.find(windowID);
			if (it != __windows__.end()) {
				r_utils::gui::Window* windowToRemove = it->second;
				__windows__.erase(it);
				if (windowToRemove) {
					delete windowToRemove;
					LOG_INFO(__logger__, "Window with ID '" + windowID + "' successfully removed and deleted.");
				}
				else {
					LOG_WARN(__logger__, "Warning: Window with ID '" + windowID + "' found in map, but pointer was nullptr. Removed from map.");
				}
			}
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


		bool Application::exists(r_utils::gui::Window* window) const
		{
			return __windows__.count(window->getID()) > 0;
		}

		bool Application::exists(std::string windowID) const
		{
			return __windows__.count(windowID) > 0;
		}

	} // gui
} // r_utils
