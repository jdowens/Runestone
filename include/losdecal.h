#ifndef _LOS_DECAL_H
#define _LOS_DECAL_H

#include<SFML/Graphics.hpp>
#include "renderabledecal.h"

namespace dtn
{
	class LOSDecal : public RenderableDecal
	{
	public :
		LOSDecal(int playerID);
		virtual void render(sf::RenderWindow& window);
	private :

	};
}
#endif