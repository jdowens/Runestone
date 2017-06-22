/*
scene.h
A base class for any runnable scene (includes graphics and input handling)
*/

#ifndef _SCENE_H
#define _SCENE_H

#include "gamescreen.h"
#include "inputhandler.h"
#include "eventmanager.h"

namespace dtn
{
	class Scene
	{
	public:
		// constructor
		Scene();

		// when attached
		virtual void onAttach(sf::RenderWindow& dest) = 0;

		// update (one loop iteration)
		virtual void update(float dt, sf::RenderWindow& window) = 0;

		// get reference to event manager
		std::shared_ptr<EventManager> getEventManager();

		// update event manager
		void updateEventManager();

		// draw the scene to the screen
		virtual void render(sf::RenderWindow& target) = 0;		
	protected:
		// data
		std::shared_ptr<Screen> m_screen;						// graphics portion
		std::shared_ptr<InputHandler> m_inputhandler;			// all input handled here
		std::shared_ptr<HUD> m_hud;
		std::shared_ptr<EventManager> m_eventManager;			// the scene's event manager
	};
}

#endif