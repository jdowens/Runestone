#ifndef _MOVEMENT_DECAL_H
#define _MOVEMENT_DECAL_H

#include<vector>
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>

#include "utilities.h"

namespace dtn
{
	class MovementDecal
	{
	public :
		MovementDecal(int playerID);
		void setVisible();
		void setInvisible();
		void setLocations(std::vector<sf::Vector2i>& moveLocs);
		void render(sf::RenderWindow& window);
	private :
		std::vector<sf::Vector2i> m_movementLocations;
		bool m_visible;
		int m_playerID;
	};
}

#endif