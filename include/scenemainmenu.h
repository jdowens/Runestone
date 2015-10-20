// scenemainmenu.h
/*
	The main menu only utilizes the HUD feature.
*/

#ifndef _SCENE_MAIN_MENU_H
#define _SCENE_MAIN_MENU_H

#include<SFML/Graphics.hpp>
#include "scene.h"
#include "HUDmainmenu.h"

namespace dtn
{
	class SceneMainMenu : public Scene
	{
	public :
		SceneMainMenu();
		virtual void onAttach(sf::RenderWindow& dest);
		virtual void update(float dt, sf::RenderWindow& window);
		virtual void render(sf::RenderWindow& target);
	private :
		
	};
}

#endif