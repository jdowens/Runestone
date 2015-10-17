#ifndef _HUD_H
#define _HUD_H

#include<sstream>

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFGUI/SFGUI.hpp>
#include<SFGUI/Widgets.hpp>

namespace dtn
{
	class HUD
	{
	public :
		HUD(int player_ID);
		void update(float dt);
		void render(sf::RenderWindow& dest);
		void handleEvent(sf::Event e);
	private :
		sfg::SFGUI sfgui;
		int m_playerMana;
		int m_opponentMana;
		int m_playerID;
		std::shared_ptr<sfg::Window> m_window;
		std::shared_ptr<sfg::Label> m_playerManaText;
		std::shared_ptr<sfg::Label> m_opponentManaText;
		void setPlayerManaText(int amount);
		void setOpponentManaText(int amount);
	};
}

#endif