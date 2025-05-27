#pragma once

#include "event/Event.h"

namespace r_utils
{
	namespace gui
	{
		namespace events
		{
			class AppQuitEvent : public r_utils::events::Event
			{
			public:
				AppQuitEvent() : r_utils::events::Event(r_utils::events::EventType::APP_QUIT) {}
				std::string toString() const override { return "AppQuitEvent"; }
			};

			class AppUpdateEvent : public r_utils::events::Event
			{
			public:
				AppUpdateEvent(double deltaTime) : r_utils::events::Event(r_utils::events::EventType::APP_UPDATE), __deltaTime__(deltaTime) {}
				double getDeltaTime() const { return __deltaTime__; }
				std::string toString() const override {
					std::stringstream ss;
					ss << "AppUpdateEvent: deltaTime=" << __deltaTime__;
					return ss.str();
				}
			private:
				double __deltaTime__;
			};

			class AppRenderEvent : public r_utils::events::Event
			{
			public:
				AppRenderEvent() : r_utils::events::Event(r_utils::events::EventType::APP_RENDER) {}
				std::string toString() const override { return "AppRenderEvent"; }
			};
		} // events
	} // gui
} // r_utils
