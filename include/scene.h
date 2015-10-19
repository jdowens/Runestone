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

		// update (one loop iteration)
		virtual void update(float dt) = 0;

		// draw the scene to the screen
		virtual void render(sf::RenderWindow& target) = 0;		
	private:

		// data
		GameScreen m_screen;									// graphics portion
		InputHandler m_inputhandler;							// all input handled here
	};
}

#endif