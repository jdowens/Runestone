#ifndef _HUD_H
#define _HUD_H

#include<sstream>

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFGUI/SFGUI.hpp>
#include<SFGUI/Widgets.hpp>

#include "globaleventqueue.h"
#include "event.h"
#include "utilities.h"

namespace dtn
{
	class HUD
	{
	public :
		HUD();
		virtual void update(float dt) = 0;
		virtual void render(sf::RenderWindow& dest) = 0;
		virtual void handleEvent(sf::Event e) = 0;
	private :
	};
}

#endif