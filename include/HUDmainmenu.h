#ifndef _HUD_MAIN_MENU_H
#define _HUD_MAIN_MENU_H

#include<SFML/Graphics/Font.hpp>
#include "HUD.h"
#include "utilities.h"

namespace dtn
{
	class HUDMainMenu : public HUD
	{
	public :
		HUDMainMenu();
		virtual void update(float dt);
		virtual void render(sf::RenderWindow& dest, sfg::SFGUI& sfgui);
		virtual void handleEvent(sf::Event e);
	private :
		sfg::Desktop m_desktop;
		std::shared_ptr<sfg::Window> m_window;
		std::shared_ptr<sfg::Box> m_guiLayout;
		std::shared_ptr<sfg::Entry> m_ipEntry;
		std::shared_ptr<sfg::Entry> m_playerNumberEntry;
		std::shared_ptr<sfg::Button> m_playOnlineButton;
		std::shared_ptr<sfg::Button> m_quitButton;
		std::shared_ptr<sfg::Label> m_testLabel;

		bool gameShouldClose;

		void onPlayOnlineButtonClicked();
		void onQuitButtonClicked();
	};
}

#endif