#pragma once

#include <string>
#include <vector>
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
			Window(const std::string& title, int width = 600, int height = 600, bool expandable = true);
			virtual ~Window();

			void show();
			void hide();
			void close();
			
			void setTitle(const std::string& title);
			void setSize(int width, int height);
			void setVisible(bool visible);
			
			std::string getTitle() const;
			std::vector<int> getSize() const;

			virtual void handleEvent(r_utils::events::Event& event);
			virtual void draw();
			void addChild(r_utils::gui::Interface* child);

		private:
			std::string __title__;
			int __width__;
			int __height__;

			bool __isVisible__;
			bool __isExpandable__;
			
			std::vector<r_utils::gui::Interface*> __children__;

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

