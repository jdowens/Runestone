/*
	eventmanager.h
	This class is an abstraction of an event queue. It allows for the attaching of listeners to
	a given event type, and for the removing of listeners from an event type.
	The class supports pushing events to the queue. All events are dispatched during the
	update() function.
*/

#ifndef _EVENTMANAGER_H
#define _EVENTMANAGER_H

// c++ includes
#include<functional>
#include<map>
#include<memory>
#include<queue>

// dtn includes
#include "event.h"

namespace dtn
{
	class EventManager
	{
	public :
		// constructor
		EventManager();
		
		// update function
		void update();

		// listener attach/remove
		int attachListener(dtn::Event::EventType type, std::function<void(
			std::shared_ptr<dtn::Event>)> f);
		void removeListener(int id);

		// push event to queue
		void pushEvent(std::shared_ptr<dtn::Event> e);
	private :
		std::queue<std::shared_ptr<dtn::Event>> m_pendingEvents;		// event queue storage
		std::map<dtn::Event::EventType,									// map of listeners
			std::map<int, std::function<void(							// maps EventType to map of listener_id to function
			std::shared_ptr<dtn::Event>)>>> m_listeners;
		std::map<dtn::Event::EventType, int> m_idCounts;				// map of id counts 
																		// (for how many listeners of each type)
		int calculateID(dtn::Event::EventType t);						// calculate id for given listener 
																		// (based on count and EventType)			
	};
}

#endif