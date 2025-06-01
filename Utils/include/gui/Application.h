#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#include "gui/Window.h"
#include "logger/Logger.h"
#include "event/IEventListener.h"
#include "event/EventDispatcher.h"
#include "gui/events/WindowEvents.h"
#include "gui/events/ApplicationEvents.h"

namespace r_utils
{
	namespace gui
	{
		class Application : public r_utils::events::IEventListener
		{
		public:
			Application(r_utils::logger::Logger* logger = nullptr);
			~Application();

			void run();
			void run(std::string& windowID);
			void registerWindow(r_utils::gui::Window* window);
			void removeWindow(r_utils::gui::Window* window);
			void removeWindow(std::string windowID);

			std::vector<r_utils::gui::Window*> getWindows() const;
			r_utils::gui::Window* getWindow(r_utils::gui::Window& window) const;
			r_utils::gui::Window* getWindow(std::string windowID) const;

			bool exists(r_utils::gui::Window* window) const;
			bool exists(std::string windowID) const;
			void stop();

			void onEvent(r_utils::events::Event& event) override;
			r_utils::events::EventDispatcher& getEventDispatcher();
		private:
			std::unordered_map<std::string, r_utils::gui::Window*> __windows__;
			std::unordered_map<std::thread::id, Window*> __threadWindows__;
			std::atomic<bool> __running__;
			std::vector<std::thread> __threads__;
			std::mutex __threadsMutex__;

			r_utils::logger::Logger* __logger__;
			r_utils::events::EventDispatcher __dispatcher__;

			void runThreadWindow(r_utils::gui::Window* window);
		};
	} // gui
} // r_utils