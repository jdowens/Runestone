#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include "screen.h"
#include "HUD.h"
#include <SFML/Graphics.hpp>

namespace dtn
{
	class InputHandler
	{
	public :
		InputHandler();
		virtual void update(sf::RenderWindow& window, std::shared_ptr<Screen> screen, 
			std::shared_ptr<HUD> HUD) = 0;
	private :
	};
}

#endif