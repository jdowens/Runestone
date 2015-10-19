// screen.h
/*
	A class that handles all of the rendering for a scene.
*/

#ifndef _SCREEN_H
#define _SCREEN_H

#include<string>
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<memory>
#include "processmanager.h"

namespace dtn
{
	class Screen
	{
		friend class InputHandler;
	public:
		// constructors
		Screen();

		// handle background texture
		void loadBackground(std::string fileName);
		void moveBackground(sf::Vector2f newLoc);

		// update function (called once per global loop)
		virtual void update(float dt);

		// render to window
		virtual void render(sf::RenderWindow& window);
	protected:
		std::shared_ptr<sf::Texture> m_backgroundTexture;
		dtn::ProcessManager m_processManager;
		sf::Sprite m_background;
	};
}

#endif