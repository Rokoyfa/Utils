#pragma once
#include <string>
#include <sstream>

namespace r_utils
{
	namespace events
	{
		enum class EventType
		{
			// NONE for NO Event
			NONE = 0,
			// APP Events
			APP_QUIT,
			APP_UPDATE,
			APP_RENDER,
			// Window Events
			WINDOW_OPEN,
			WINDOW_CLOSE,
			WINDOW_RESIZE,
			WINDOW_FOCUS,
			WINDOW_LOST_FOCUS,
			WINDOW_MOVED,
			// Mouse Events
			MOUSE_MOVE,
			MOUSE_SCROLLED,
			MOUSE_BUTTON_PRESSED,
			MOUSE_BUTTON_RELEASED,
			// Key Events
			KEY_PRESSED,
			KEY_RELEASED,
			KEY_TYPED,
		};

		enum class MouseButton
		{
			None = 0,
			Left = 1,
			Right = 2,
			Middle = 4
		};

		enum class KeyModifier
		{
			None = 0,
			Shift = 1,
			Control = 2,
			Alt = 4
		};

		class Event
		{
		public:
			Event(EventType type) : __type__(type), __handled__(false) {}
			virtual ~Event() = default;

			EventType getType() const;

			void setHandled(bool handled);
			bool isHandled() const;

			virtual std::string toString() const;
		protected:
			EventType __type__;
			bool __handled__;
		};
	} // events
} // r_utils