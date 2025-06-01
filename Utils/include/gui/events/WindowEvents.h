#pragma once

#include "event/Event.h"

namespace r_utils
{
	namespace gui
	{
		namespace events
		{

			class WindowVisibleEvent : public r_utils::events::Event
			{
			public:
				WindowVisibleEvent(bool visible) : r_utils::events::Event(r_utils::events::EventType::WINDOW_VISIBLE), __visible__(visible) {}
				bool isVisible() const { return __visible__; }
				std::string toString() const override { return "WindowVisibleEvent"; }
			private:
				bool __visible__;
			};

			class WindowShowEvent : public r_utils::events::Event
			{
			public:
				WindowShowEvent() : r_utils::events::Event(r_utils::events::EventType::WINDOW_SHOW) { WindowVisibleEvent(true); }
				std::string toString() const override { return "WindowShowEvent"; }
			};

			class WindowHideEvent : public r_utils::events::Event
			{
			public:
				WindowHideEvent() : r_utils::events::Event(r_utils::events::EventType::WINDOW_HIDE) { WindowVisibleEvent(false); }
				std::string toString() const override { return "WindowHideEvent"; }
			};

			class WindowCloseEvent : public r_utils::events::Event
			{
			public:
				WindowCloseEvent(std::string WId) : r_utils::events::Event(r_utils::events::EventType::WINDOW_CLOSE), __WId__(WId) {}
				std::string toString() const override { return "WindowCloseEvent"; }
				std::string getId() const { return __WId__; }
			private:
				std::string __WId__;
			};

			class WindowResizeEvent : public r_utils::events::Event
			{
			public:
				WindowResizeEvent(int width, int height)
					: r_utils::events::Event(r_utils::events::EventType::WINDOW_RESIZE), __width__(width), __height__(height) {}

				int getWidth() const { return __width__; }
				int getHeight() const { return __height__; }

				std::string toString() const override {
					std::stringstream ss;
					ss << "WindowResizeEvent: " << __width__ << "x" << __height__;
					return ss.str();
				}
			private:
				int __width__, __height__;
			};

			class WindowFocusEvent : public r_utils::events::Event
			{
			public:
				WindowFocusEvent() : r_utils::events::Event(r_utils::events::EventType::WINDOW_FOCUS) {}
				std::string toString() const override { return "WindowFocusEvent"; }
			};

			class WindowLostFocusEvent : public r_utils::events::Event
			{
			public:
				WindowLostFocusEvent() : r_utils::events::Event(r_utils::events::EventType::WINDOW_LOST_FOCUS) {}
				std::string toString() const override { return "WindowLostFocusEvent"; }
			};

			class WindowMovedEvent : public r_utils::events::Event
			{
			public:
				WindowMovedEvent(int x, int y) : r_utils::events::Event(r_utils::events::EventType::WINDOW_MOVED), __x__(x), __y__(y) {}
				int getX() const { return __x__; }
				int getY() const { return __y__; }
				std::string toString() const override {
					std::stringstream ss;
					ss << "WindowMovedEvent: (" << __x__ << ", " << __y__ << ")";
					return ss.str();
				}
			private:
				int __x__, __y__;
			};
		} // events
	} // gui
} // r_utils