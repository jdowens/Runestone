#ifndef _HUD_H
#define _HUD_H

#include<sstream>

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<TGUI/TGUI.hpp>

#include "globaleventqueue.h"
#include "event.h"
#include "utilities.h"

namespace dtn
{
	class HUD
	{
	public :
		HUD(sf::RenderWindow& dest);
		virtual void update(float dt) = 0;
		virtual void render(sf::RenderWindow& dest);
		virtual void handleEvent(sf::Event e) = 0;
	protected :
		static std::shared_ptr<tgui::Gui> m_GUI;
	};
}

#endif