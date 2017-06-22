#include "scene.h"

dtn::Scene::Scene()
{

}

std::shared_ptr<dtn::EventManager> dtn::Scene::getEventManager()
{
	return m_eventManager;
}

void dtn::Scene::updateEventManager()
{
	if (m_eventManager != NULL)
		m_eventManager->update();
	else
		std::cout << "Event manager attempt to update with no event manager attached!\n";
}
