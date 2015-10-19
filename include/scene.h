/*
scene.h
A base class for any runnable scene (includes graphics and input handling)
*/

#ifndef _SCENE_H
#define _SCENE_H

#include "gamescreen.h"
#include "inputhandler.h"

namespace dtn
{
	class Scene
	{
	public:
		// constructor
		Scene();

		// when attached
		virtual void onAttach() = 0;

		// update (one loop iteration)
		virtual void update(float dt, sf::RenderWindow& window) = 0;

		// draw the scene to the screen
		virtual void render(sf::RenderWindow& target, sfg::SFGUI& sfgui) = 0;		
	protected:
		// data
		std::shared_ptr<Screen> m_screen;						// graphics portion
		std::shared_ptr<InputHandler> m_inputhandler;			// all input handled here
		std::shared_ptr<HUD> m_hud;
	};
}

#endif