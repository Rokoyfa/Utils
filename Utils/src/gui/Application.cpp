#include "gui/Application.h"
#include "exception/gui/WindowApplicationException.h"

namespace r_utils
{
	namespace gui
	{
		Application::Application()
		{
		}

		Application::~Application()
		{
		}


		void Application::createWindow(r_utils::gui::Window* window)
		{
			if (exists(window->getID()))
			{
				throw r_utils::exception::WindowApplicationException("Error: Window with ID '" + window->getID() + "' already exists!");
				return;
			}

			__windows__[window->getID()] = window;
		}

		void Application::removeWindow(r_utils::gui::Window* window)
		{
			removeWindow(window->getID());
		}

		void Application::removeWindow(std::string windowID)
		{
			if (!exists(windowID))
			{
				throw r_utils::exception::WindowApplicationException("Error: Window with ID '" + windowID + "' doesnt exists!");
				return;
			}

			__windows__.erase(windowID);
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

	}
}
