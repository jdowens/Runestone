#include "globaleventqueue.h"

std::shared_ptr<dtn::GlobalEventQueue> dtn::GlobalEventQueue::m_instance = NULL;

dtn::GlobalEventQueue::GlobalEventQueue()
{

}

std::shared_ptr<dtn::GlobalEventQueue> dtn::GlobalEventQueue::getInstance()
{
	if (m_instance == NULL)
		m_instance = std::shared_ptr<dtn::GlobalEventQueue>(new dtn::GlobalEventQueue());
	return m_instance;
}

void dtn::GlobalEventQueue::update()
{
	m_eventmanager.update();
}

int dtn::GlobalEventQueue::attachListener(dtn::Event::EventType type, std::function < void(
	std::shared_ptr<dtn::Event>) > f)
{
	return m_eventmanager.attachListener(type, f);
}

void dtn::GlobalEventQueue::removeListener(int id)
{
	m_eventmanager.removeListener(id);
}

void dtn::GlobalEventQueue::pushEvent(std::shared_ptr<dtn::Event> e)
{
	m_eventmanager.pushEvent(e);
}

bool dtn::GlobalEventQueue::pendingEvents()
{
	return m_eventmanager.pendingEvents();
}