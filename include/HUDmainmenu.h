#ifndef _HUD_MAIN_MENU_H
#define _HUD_MAIN_MENU_H

#include<SFML/Graphics.hpp>
#include<TGUI/TGUI.hpp>
#include "scenemanager.h"
#include "scenemultiplayermatch.h"
#include "HUD.h"
#include "utilities.h"
#include "globaleventqueue.h"

namespace dtn
{
	class HUDMainMenu : public HUD
	{
	public :
		HUDMainMenu(sf::RenderWindow& dest);
		~HUDMainMenu();
		virtual void update(float dt);
		virtual void handleEvent(sf::Event e);
	private :
		tgui::VerticalLayout::Ptr m_layout;
		tgui::EditBox::Ptr m_ipAddressEntry;
		tgui::EditBox::Ptr m_playerNumberEntry;
		tgui::Button::Ptr m_playOnlineButton;
		tgui::Button::Ptr m_quitButton;
		void onPlayOnlineButtonClicked();
		void onQuitButtonClicked();
	};
}

#endif