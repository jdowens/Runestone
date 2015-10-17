#include "movementdecal.h"

dtn::MovementDecal::MovementDecal(int playerID)
{
	m_playerID = playerID;
	m_visible = false;
}

void dtn::MovementDecal::setVisible()
{
	m_visible = true;
}

void dtn::MovementDecal::setInvisible()
{
	m_visible = false;
}

void dtn::MovementDecal::setLocations(std::vector<sf::Vector2i>& moveLocs)
{
	m_movementLocations.clear();
	for (auto it = moveLocs.begin(); it != moveLocs.end(); ++it)
	{
		m_movementLocations.push_back(*it);
	}
}

void dtn::MovementDecal::render(sf::RenderWindow & window)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(dtn::Utilities::PIXELS_PER_TILE_X, dtn::Utilities::PIXELS_PER_TILE_Y));
	shape.setFillColor(sf::Color::Green);
	shape.setFillColor(sf::Color(0, 255, 0, 63));

	for (auto it = m_movementLocations.begin(); it != m_movementLocations.end(); ++it)
	{
		shape.setPosition(dtn::Utilities::TileToFloat(dtn::Utilities::LocalTileToGlobal(
			*it, m_playerID)));
		window.draw(shape);
	}
}
