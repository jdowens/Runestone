#ifndef _MOVEMENT_DECAL_H
#define _MOVEMENT_DECAL_H

#include<vector>
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>

#include "utilities.h"
#include "renderabledecal.h"

namespace dtn
{
	class MovementDecal : public RenderableDecal
	{
	public :
		MovementDecal(int playerID);
		virtual void render(sf::RenderWindow& window);
	private :
	};
}

#endif