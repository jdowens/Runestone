#ifndef _HUD_GAME_H
#define _HUD_GAME_H

#include "HUD.h"
#include "utilities.h"
#include "widgetutilities.h"

namespace dtn
{
	class HUDgame : public HUD
	{
	public:
		HUDgame(int player_ID, sf::RenderWindow& dest);
		~HUDgame();
		virtual void update(float dt);
		virtual void handleEvent(sf::Event e);
	private:
		int m_playerMana;
		int m_opponentMana;
		int m_playerID;
		tgui::Label::Ptr m_playerManaText;
		tgui::Label::Ptr m_opponentManaText;
		tgui::Button::Ptr m_endTurnButton;
		void setPlayerManaText(int amount);
		void setOpponentManaText(int amount);

		// listeners
		void onManaChanged(std::shared_ptr<dtn::Event> e);
		void onEndTurnButtonClicked();
	};
}


#endif