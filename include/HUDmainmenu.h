#ifndef _HUD_MAIN_MENU_H
#define _HUD_MAIN_MENU_H

#include<SFML/Graphics.hpp>
#include "scenemanager.h"
#include "gameclient.h"
#include "HUD.h"
#include "utilities.h"

namespace dtn
{
	class HUDMainMenu : public HUD
	{
	public :
		HUDMainMenu();
		~HUDMainMenu();
		virtual void update(float dt);
		virtual void render(sf::RenderWindow& dest);
		virtual void handleEvent(sf::Event e);
	private :
		sfg::Desktop m_desktop;
		std::shared_ptr<sfg::Window> m_window;
		std::shared_ptr<sfg::Box> m_guiLayout;
		std::shared_ptr<sfg::Entry> m_ipEntry;
		std::shared_ptr<sfg::Entry> m_playerNumberEntry;
		std::shared_ptr<sfg::Button> m_playOnlineButton;
		std::shared_ptr<sfg::Button> m_quitButton;
		sf::RectangleShape m_stupidRectThatHasToBeDrawn;

		void onPlayOnlineButtonClicked();
		void onQuitButtonClicked();
	};
}

#endif