#include "eventmanager.h"

// [4] Step 4 in the addition of an event type
dtn::EventManager::EventManager()
{
	m_idCounts[dtn::Event::EventType::ADD_RENDERABLE] = 0;
	m_idCounts[dtn::Event::EventType::CLICK_AND_DRAG] = 0;
	m_idCounts[dtn::Event::EventType::DELETE_RENDERABLE] = 0;
	m_idCounts[dtn::Event::EventType::END_TURN] = 0;
	m_idCounts[dtn::Event::EventType::ENTITY_ADDED] = 0;
	m_idCounts[dtn::Event::EventType::ENTITY_BATTLE] = 0;
	m_idCounts[dtn::Event::EventType::ENTITY_DRAWN] = 0;
	m_idCounts[dtn::Event::EventType::ENTITY_MOVED] = 0;
	m_idCounts[dtn::Event::EventType::GAME_QUIT] = 0;
	m_idCounts[dtn::Event::EventType::MOUSE_HOVERED] = 0;
	m_idCounts[dtn::Event::EventType::MOVE_RENDERABLE] = 0;
	m_idCounts[dtn::Event::EventType::RUNESTONE_ATTACK] = 0;
	m_idCounts[dtn::Event::EventType::RUNESTONE_DRAW] = 0;
	m_idCounts[dtn::Event::EventType::RUNESTONE_MOVE] = 0;
	m_idCounts[dtn::Event::EventType::RUNESTONE_PLAY] = 0;
	m_idCounts[dtn::Event::EventType::SINGLE_CLICK] = 0;
	m_idCounts[dtn::Event::EventType::UNKNOWN] = 0;
	m_idCounts[dtn::Event::EventType::UPDATE_RENDERABLE_LOS] = 0;
	m_idCounts[dtn::Event::EventType::UPDATE_RENDERABLE_OWNER] = 0;
	m_idCounts[dtn::Event::EventType::UPDATE_RENDERABLE_TOOLTIP] = 0;
	m_idCounts[dtn::Event::EventType::MANA_CHANGED] = 0;
	m_idCounts[dtn::Event::EventType::ENTITY_MOVE_FLAG_CHANGED] = 0;
	m_idCounts[dtn::Event::EventType::ALL_EVENTS] = 0;
}

// update
/*
	This function takes care of calling all of the events in the queue.
*/
void dtn::EventManager::update()
{
	while (!m_pendingEvents.empty())
	{
		std::shared_ptr<dtn::Event> cur = m_pendingEvents.front();
		m_pendingEvents.pop();
		// get map of listeners for particular cur->eventType
		std::map<int, std::function<void(
			std::shared_ptr<dtn::Event>) >> m_currentMap = m_listeners[cur->getType()];
		for (std::map<int, std::function<void(
			std::shared_ptr<dtn::Event>) >> ::iterator it = m_currentMap.begin();
			it != m_currentMap.end(); ++it)
		{
			it->second(cur);
		}
		// get map of listeners corresponding to the global_listeners
		m_currentMap = m_listeners[dtn::Event::EventType::ALL_EVENTS];
		for (std::map<int, std::function<void(
			std::shared_ptr<dtn::Event>) >> ::iterator it = m_currentMap.begin();
			it != m_currentMap.end(); ++it)
		{
			it->second(cur);
		}
	}
}

// pendingEvents
/*
	Returns true if there are pending events in the queue
*/
bool dtn::EventManager::pendingEvents()
{
	return m_pendingEvents.size() > 0;
}

// attachListener
/*
	Attaches a listener to a given EventType
*/
int dtn::EventManager::attachListener(dtn::Event::EventType type, std::function < void(
	std::shared_ptr<dtn::Event>) > f)
{
	int id = calculateID(type);
	m_listeners[type].insert({ id, f });
	return id;
}

// removeListener
/*
	Removes a listener from a given EventType
*/
void dtn::EventManager::removeListener(int id)
{
	dtn::Event::EventType type = (dtn::Event::EventType)(id >> 24);
	std::map<int, std::function<void(
		std::shared_ptr<dtn::Event>) >> ::iterator it = m_listeners[type].find(id);
	if (it != m_listeners[type].end())
	{
		m_listeners[type].erase(it);
	}
}

// calculateID
int dtn::EventManager::calculateID(dtn::Event::EventType t)
{
	_Uint32t id = (_Uint32t)t << 24;
	m_idCounts[t]++;
	id = id | m_idCounts[t];
	return id;
}

// pushEvent
void dtn::EventManager::pushEvent(std::shared_ptr<dtn::Event> e)
{
	m_pendingEvents.push(e);
}
