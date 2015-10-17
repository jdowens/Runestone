#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include<vector>
#include<memory>
#include<SFML/System/Vector2.hpp>
#include "event.h"
#include "gamescreen.h"
#include "renderable.h"
#include "globaleventqueue.h"
#include "HUD.h"

namespace dtn
{
	class InputHandler
	{
	public :
		InputHandler(int playerID);
		void update(sf::RenderWindow& window, dtn::GameScreen& screen, dtn::HUD& HUD);
	private :
		void updateHovered(dtn::GameScreen& screen);
		void handleEvents(sf::RenderWindow& window, dtn::HUD& HUD);
		sf::Vector2i m_mousePos;
		std::shared_ptr<dtn::Renderable> m_hovered;
		std::shared_ptr<dtn::Renderable> m_selected;
		int m_playerID;
		sf::IntRect m_summoningZone;
		sf::IntRect m_handZone;
		sf::IntRect m_battlefieldZone;
	};
}

#endif