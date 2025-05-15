#pragma once

#include <string>
#include <vector>
#include <functional>
#include "event/Event.h"
#include "gui/interface/Interface.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace r_utils
{
	namespace gui
	{
		class Window
		{
		public:
			Window(std::string id, const std::string& title, int width = 600, int height = 600, bool expandable = true);
			virtual ~Window();

			void updateWindow(MSG msg);

			void show();
			void hide();
			void close();
			
			void setTitle(const std::string& title);
			void setSize(int width, int height);
			void setVisible(bool visible);
			void setIconPath(std::string& iconPath);
			
			std::string getTitle() const;
			std::string getIcon() const;
			std::vector<int> getSize() const;
			std::string getID() const;

			virtual void handleEvent(r_utils::events::Event& event);
			virtual void draw();
			void addChild(r_utils::gui::Interface* child);
			
			using EventCallback = std::function<void(const r_utils::events::Event&)>;
			void addEventListener(const std::string& eventType, EventCallback callback);
		private:
			std::string __id__;
			std::string __title__;
			std::string __iconPath__ = "storage\\apps\\style\\Icon.ico";
			int __width__;
			int __height__;

			bool __isVisible__;
			bool __isExpandable__;
			
			std::vector<r_utils::gui::Interface*> __children__;
			std::unordered_map<std::string, std::vector<EventCallback>> __listeners__;
#ifdef _WIN32
			HWND __hwnd__;

		public:
			const HWND& getHWND() const;
#endif
#ifdef __linux__
			unsigned long __xid__;
#endif
#ifdef __APPLE__
			void* __nsWindow__;
#endif
		};
	}
}

