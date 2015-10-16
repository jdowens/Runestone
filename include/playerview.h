#ifndef _PLAYERVIEW_H
#define _PLAYERVIEW_H

#include<sstream>
#include<fstream>
#include<iostream>
#include<memory>
#include "view.h"
#include "runestonedatabase.h"
#include "gamescreen.h"
#include "processmoverenderable.h"
#include "processmanager.h"
#include "event.h"
#include "tooltip.h"

namespace dtn
{
	class PlayerView : public View
	{
	public :
		PlayerView(int playerID);
		std::vector<std::shared_ptr<dtn::Event>> Update(
			std::vector<std::shared_ptr<dtn::Event>> events);
	private :
		void updateHovered();
		void handleEventList(std::vector<std::shared_ptr<dtn::Event>> events);
		void handleEvent(sf::Event event);
		void render();
		void renderOtherPlayerCards();
		void renderMisc();
		dtn::GameScreen m_screen;
		sf::RenderWindow m_window;
		sf::Vector2i m_mousePos;
		dtn::Player m_player;
		dtn::Battlefield m_battlefield;
		sf::Clock m_clock;
		dtn::Tooltip m_tooltip;
		std::vector<std::shared_ptr<dtn::Event>> m_returnEvents;
		std::shared_ptr<dtn::EntityBattlefield> m_hovered;
		std::shared_ptr<dtn::EntityBattlefield> m_selected;
		int m_player2Cards;
		int m_player2DeckAmount;
		bool m_isTurn;
		bool m_tooltipActive;
		///////// Event Encapsulating Functions
		void draw();
	};
}
#endif