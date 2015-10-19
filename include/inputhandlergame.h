#ifndef _INPUTHANDLERGAME_H
#define _INPUTHANDLERGAME_H

#include<vector>
#include<memory>
#include<SFML/System/Vector2.hpp>
#include<SFML/Graphics.hpp>
#include "inputhandler.h"
#include "HUD.h"
#include "screen.h"
#include "gamescreen.h"

namespace dtn
{
	class InputHandlerGame : public InputHandler
	{
	public:
		InputHandlerGame(int playerID);
		virtual void update(sf::RenderWindow& window, std::shared_ptr<Screen> screen,
			std::shared_ptr<HUD> HUD);
	private:
		void updateHovered(GameScreen* screen);
		void handleEvents(sf::RenderWindow& window, GameScreen* screen,
			std::shared_ptr<HUD> hud);
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