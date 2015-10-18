#ifndef _RENDERABLE_DECAL_H
#define _RENDERABLE_DECAL_H

#include<vector>
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>

#include "utilities.h"

namespace dtn
{
	class RenderableDecal
	{
	public:
		RenderableDecal(int playerID);
		void setVisible();
		void setInvisible();
		void setLocations(std::vector<sf::Vector2i>& locs);
		virtual void render(sf::RenderWindow& window) = 0;
	protected:
		std::vector<sf::Vector2i> m_locations;
		bool m_visible;
		int m_playerID;
	};
}

#endif