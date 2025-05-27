#include "event/Event.h"

namespace r_utils
{
	namespace events
	{
		EventType Event::getType() const
		{
			return __type__;
		}

		void Event::setHandled(bool handled)
		{
			__handled__ = handled;
		}

		bool Event::isHandled() const
		{
			return __handled__;
		}

		std::string Event::toString() const
		{
			std::stringstream ss;
			ss << "Event: " << static_cast<int>(__type__);

			return ss.str();
		}
	} // events
} // r_utils