#pragma once

#include <string>
#include <vector>
#include <functional>

#include "event/Event.h"
#include "gui/interface/Interface.h"
#include "logger/Logger.h"

#include "event/IEventListener.h"
#include "event/EventDispatcher.h"
#include "gui/events/WindowEvents.h"
#include "event/events/InputEvents.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace r_utils
{
	namespace gui
	{
		class Window : public r_utils::events::IEventListener
		{
		public:
			Window(std::string id, const std::string& title, r_utils::events::EventDispatcher& dispatcher, int width = 600, int height = 600, r_utils::logger::Logger* logger = nullptr);
			Window(std::string id, const std::string& title, r_utils::events::EventDispatcher& dispatcher, r_utils::logger::Logger* logger = nullptr);
			virtual ~Window();

			void show();
			void hide();
			void close();
			
			void setTitle(const std::string& title);
			void setSize(int width, int height);
			void setVisible(bool visible);
			void setIconPath(const std::string& iconPath);
			
			std::string getTitle() const;
			std::string getIconPath() const;
			std::vector<int> getSize() const;
			std::string getID() const;

			virtual void onEvent(r_utils::events::Event& event) override;
			virtual void draw();
			void addChild(r_utils::gui::Interface* child);
		private:
			std::string __id__;
			std::string __title__;
			std::string __iconPath__ = "storage\\apps\\style\\Icon.ico";
			int __width__;
			int __height__;

			bool __isVisible__;
			
			std::vector<r_utils::gui::Interface*> __children__;
			r_utils::logger::Logger* __logger__;
			r_utils::events::EventDispatcher& __dispatcher__;

			void updateWindow(MSG& msg);
#ifdef _WIN32
			HWND __hwnd__;
			DWORD __winThreadId__;

		public:
			static std::unordered_map<HWND, Window*> __windowMap__;
			static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			bool createWinWindow();

			DWORD getWinThreadId() const;
			const HWND& getHWND() const;
#endif
#ifdef __linux__
			unsigned long __xid__;
#endif
#ifdef __APPLE__
			void* __nsWindow__;
#endif
		};
	} // gui
} // r_utils

