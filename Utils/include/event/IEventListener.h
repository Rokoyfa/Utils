#pragma once

#include "event/Event.h"
namespace r_utils
{
	namespace events
	{
		class IEventListener
		{
		public:
			virtual ~IEventListener() = default;

			virtual void onEvent(Event& event) = 0;
		};
	} // events
} // r_utils