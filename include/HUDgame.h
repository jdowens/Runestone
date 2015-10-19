#ifndef _HUD_GAME_H
#define _HUD_GAME_H

#include "HUD.h"
#include "utilities.h"

namespace dtn
{
	class HUDgame : public HUD
	{
	public:
		HUDgame(int player_ID);
		virtual void update(float dt);
		virtual void render(sf::RenderWindow& dest, sfg::SFGUI& sfgui);
		virtual void handleEvent(sf::Event e);
	private:
		int m_playerMana;
		int m_opponentMana;
		int m_playerID;
		std::shared_ptr<sfg::Window> m_window;
		std::shared_ptr<sfg::Box> m_guiLayout;
		std::shared_ptr<sfg::Label> m_playerManaText;
		std::shared_ptr<sfg::Label> m_opponentManaText;
		std::shared_ptr<sfg::Button> m_endTurnButton;
		void setPlayerManaText(int amount);
		void setOpponentManaText(int amount);

		// listeners
		void onManaChanged(std::shared_ptr<dtn::Event> e);
		void onEndTurnButtonClicked();
	};
}


#endif