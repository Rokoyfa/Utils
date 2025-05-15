#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <thread>

#include "gui/Window.h"

namespace r_utils
{
	namespace gui
	{
		class Application
		{
		public:
			Application();
			~Application();

			void run();
			void createWindow(r_utils::gui::Window* window);
			void removeWindow(r_utils::gui::Window* window);
			void removeWindow(std::string windowID);

			std::vector<r_utils::gui::Window*> getWindows() const;
			r_utils::gui::Window* getWindow(r_utils::gui::Window& window) const;
			r_utils::gui::Window* getWindow(std::string windowID) const;

			bool exists(r_utils::gui::Window* window) const;
			bool exists(std::string windowID) const;
		private:
			std::unordered_map<std::string, r_utils::gui::Window*> __windows__;
			std::unordered_map<std::thread, r_utils::gui::Window*> __threads__;

			void runThreadWindow();
		};
	}
}