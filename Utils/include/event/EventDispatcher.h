#pragma once

#include <vector>
#include <functional>
#include <algorithm>

#include "event/Event.h"
#include "event/IEventListener.h"

namespace r_utils
{
	namespace events
	{
		class EventDispatcher
		{
		public:
			EventDispatcher();
			~EventDispatcher();

			void addListener(IEventListener* listener);

			void removeListener(IEventListener* listener);

			void dispatch(Event& event);

		private:
			std::vector<IEventListener*> __listeners__;
		};
	} // namespace events
} // namespace r_utils