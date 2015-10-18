#include "renderabledecal.h"

dtn::RenderableDecal::RenderableDecal(int playerID)
{
	m_playerID = playerID;
	m_visible = false;
}

void dtn::RenderableDecal::setVisible()
{
	m_visible = true;
}

void dtn::RenderableDecal::setInvisible()
{
	m_visible = false;
}

void dtn::RenderableDecal::setLocations(std::vector<sf::Vector2i>& locs)
{
	m_locations.clear();
	for (auto it = locs.begin(); it != locs.end(); ++it)
	{
		m_locations.push_back(*it);
	}
}