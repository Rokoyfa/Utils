#include "event/EventDispatcher.h"
#include <iostream>

namespace r_utils
{
	namespace events
	{
		EventDispatcher::EventDispatcher()
		{}

		EventDispatcher::~EventDispatcher()
		{
			__listeners__.clear();
		}

		void EventDispatcher::addListener(IEventListener* listener)
		{
			if (listener) {
				for (const auto& existingListener : __listeners__) {
					if (existingListener == listener) {
						return;
					}
				}
				__listeners__.push_back(listener);
			}
		}

		void EventDispatcher::removeListener(IEventListener* listener)
		{
			if (listener) {
				__listeners__.erase(
					std::remove_if(__listeners__.begin(), __listeners__.end(),
						[listener](IEventListener* l) { return l == listener; }),
					__listeners__.end()
				);
			}
		}

		void EventDispatcher::dispatch(Event& event)
		{
			std::vector<IEventListener*> listenersCopy = __listeners__;

			for (IEventListener* listener : listenersCopy) {
				if (event.isHandled()) {
					break;
				}
				listener->onEvent(event);
			}
		}
	} // namespace events
} // namespace r_utils