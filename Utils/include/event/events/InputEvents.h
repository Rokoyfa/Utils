#pragma once

#include "event/Event.h"

namespace r_utils
{
	namespace events 
	{
		class MouseMovedEvent : public r_utils::events::Event
		{
		public:
			MouseMovedEvent(int x, int y)
				: r_utils::events::Event(r_utils::events::EventType::MOUSE_MOVED), __x__(x), __y__(y) {}

			int getX() const { return __x__; }
			int getY() const { return __y__; }

			std::string toString() const override {
				std::stringstream ss;
				ss << "MouseMovedEvent: (" << __x__ << ", " << __y__ << ")";
				return ss.str();
			}
		private:
			int __x__, __y__;
		};

		class MouseScrolledEvent : public r_utils::events::Event
		{
		public:
			MouseScrolledEvent(double xOffset, double yOffset)
				: r_utils::events::Event(r_utils::events::EventType::MOUSE_SCROLLED), __xOffset__(xOffset), __yOffset__(yOffset) {}

			double getXOffset() const { return __xOffset__; }
			double getYOffset() const { return __yOffset__; }

			std::string toString() const override {
				std::stringstream ss;
				ss << "MouseScrolledEvent: xOffset=" << __xOffset__ << ", yOffset=" << __yOffset__;
				return ss.str();
			}
		private:
			double __xOffset__, __yOffset__;
		};


		class MouseButtonPressedEvent : public r_utils::events::Event
		{
		public:
			MouseButtonPressedEvent(MouseButton button, int x, int y)
				: r_utils::events::Event(r_utils::events::EventType::MOUSE_BUTTON_PRESSED), __button__(button), __x__(x), __y__(y) {}

			MouseButton getButton() const { return __button__; }
			int getX() const { return __x__; }
			int getY() const { return __y__; }

			std::string toString() const override {
				std::stringstream ss;
				ss << "MouseButtonPressedEvent: Button=" << static_cast<int>(__button__)
					<< " at (" << __x__ << ", " << __y__ << ")";
				return ss.str();
			}
		private:
			MouseButton __button__;
			int __x__, __y__;
		};

		class MouseButtonReleasedEvent : public r_utils::events::Event
		{
		public:
			MouseButtonReleasedEvent(MouseButton button, int x, int y)
				: r_utils::events::Event(r_utils::events::EventType::MOUSE_BUTTON_RELEASED), __button__(button), __x__(x), __y__(y) {}

			MouseButton getButton() const { return __button__; }
			int getX() const { return __x__; }
			int getY() const { return __y__; }

			std::string toString() const override {
				std::stringstream ss;
				ss << "MouseButtonReleasedEvent: Button=" << static_cast<int>(__button__)
					<< " at (" << __x__ << ", " << __y__ << ")";
				return ss.str();
			}
		private:
			MouseButton __button__;
			int __x__, __y__;
		};


		class KeyPressedEvent : public Event
		{
		public:
			KeyPressedEvent(int keyCode, KeyModifier modifiers, bool isRepeat = false)
				: Event(EventType::KEY_PRESSED), __keyCode__(keyCode), __modifiers__(modifiers), __isRepeat__(isRepeat) {}

			int getKeyCode() const { return __keyCode__; }
			KeyModifier getModifiers() const { return __modifiers__; }
			bool isRepeat() const { return __isRepeat__; }

			std::string toString() const override {
				std::stringstream ss;
				ss << "KeyPressedEvent: Key=" << __keyCode__
					<< ", Modifiers=" << static_cast<int>(__modifiers__)
					<< ", Repeat=" << (__isRepeat__ ? "true" : "false");
				return ss.str();
			}
		private:
			int __keyCode__;
			KeyModifier __modifiers__;
			bool __isRepeat__;
		};

		class KeyReleasedEvent : public Event
		{
		public:
			KeyReleasedEvent(int keyCode, KeyModifier modifiers)
				: Event(EventType::KEY_RELEASED), __keyCode__(keyCode), __modifiers__(modifiers) {}

			int getKeyCode() const { return __keyCode__; }
			KeyModifier getModifiers() const { return __modifiers__; }

			std::string toString() const override {
				std::stringstream ss;
				ss << "KeyReleasedEvent: Key=" << __keyCode__
					<< ", Modifiers=" << static_cast<int>(__modifiers__);
				return ss.str();
			}
		private:
			int __keyCode__;
			KeyModifier __modifiers__;
		};

		class KeyTypedEvent : public Event
		{
		public:
			KeyTypedEvent(int character)
				: Event(EventType::KEY_TYPED), __character__(character) {}

			int getCharacter() const { return __character__; }

			std::string toString() const override {
				std::stringstream ss;
				ss << "KeyTypedEvent: Char=" << static_cast<char>(__character__);
				return ss.str();
			}
		private:
			int __character__;
		};
	} // events
} // r_utils