#pragma once

#include <string>
#include <deque>
#include <mutex>

#include "gui/Window.h"
#include "RUtils.h"

namespace r_utils
{
	namespace logger
	{
		namespace window
		{
			class LoggerWindow : public r_utils::gui::Window
			{
			public:
				LoggerWindow(const LoggerWindow&) = delete;
				LoggerWindow& operator=(const LoggerWindow&) = delete;

				static LoggerWindow& getInstance();

				void logToGUI(const std::string& msg);
				void draw() override;
				void handleEvent(r_utils::events::Event& event) override;

			private:
				LoggerWindow(std::string id = "LoggerWindow", const std::string& title = "Application Log", int width = 800, int height = 600);
				~LoggerWindow();

				std::deque<std::string> __logMessages__;
				std::mutex __logMutex__;
				const size_t __maxLogLines__ = 100;

				void drawLogText(HDC hdc);
			};
		}
	}
}