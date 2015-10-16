#ifndef _GLOBALEVENTQUEUE_H
#define _GLOBALEVENTQUEUE_H

#include<memory>
#include<functional>
#include<string>

#include "eventmanager.h"
#include "event.h"

namespace dtn
{
	class GlobalEventQueue
	{
	public:
		static std::shared_ptr<dtn::GlobalEventQueue> getInstance();
		void update();
		int attachListener(dtn::Event::EventType type, std::function<void(
			std::shared_ptr<dtn::Event>)> f);
		void removeListener(int id);
		void pushEvent(std::shared_ptr<dtn::Event> e);
	private:
		GlobalEventQueue();
		static std::shared_ptr<dtn::GlobalEventQueue> m_instance;
		dtn::EventManager m_eventmanager;
	};
}

#endif