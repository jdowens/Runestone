#include "movementdecal.h"

dtn::MovementDecal::MovementDecal(int playerID)
	:RenderableDecal(playerID)
{

}

void dtn::MovementDecal::render(sf::RenderWindow & window)
{
	if (m_visible)
	{
		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(dtn::Utilities::PIXELS_PER_TILE_X, dtn::Utilities::PIXELS_PER_TILE_Y));
		shape.setFillColor(sf::Color(0, 255, 0, 127));

		for (auto it = m_locations.begin(); it != m_locations.end(); ++it)
		{
			shape.setPosition(dtn::Utilities::TileToFloat(dtn::Utilities::LocalTileToGlobal(
				*it, m_playerID)));
			window.draw(shape);
		}
	}
}
