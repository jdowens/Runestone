/*
	gamescreen.h
	This is the base class for all other derived game screens.
*/
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

// c++ includes
#include<vector>
#include<iostream>
#include<memory>
#include<fstream>
#include<functional>

// SFML includes
#include<SFML/Graphics.hpp>

// dtn includes
#include "globaleventqueue.h"
#include "renderablefactory.h"
#include "renderable.h"
#include "utilities.h"
#include "event.h"
#include "processmanager.h"
#include "processmoverenderable.h"
#include "processshakerenderable.h"
#include "tooltip.h"
#include "movementdecal.h"

namespace dtn
{
	class GameScreen
	{
		friend class InputHandler;
	public :
		// constructors
		GameScreen(std::shared_ptr<sf::Texture> background, int playerID);
		GameScreen(int playerID);

		// handle background texture
		void loadBackground(std::string fileName);
		void moveBackground(sf::Vector2f newLoc);

		// update function (called once per global loop)
		void update(float dt);

		// render to window
		void render(sf::RenderWindow& window, int playerID);
		
		// handle the addition/removal of renderables
		void pushRenderable(int entityID, std::shared_ptr<dtn::Renderable> renderable);
		void removeRenderable(int entityID);

		// get renderable at a pixel position
		std::shared_ptr<dtn::Renderable> getRenderableAt(sf::Vector2i position);
		std::shared_ptr<dtn::Renderable> getRenderableAt(sf::Vector2f position);
	private :
		std::map<int, std::shared_ptr<dtn::Renderable>> m_renderables;
		std::shared_ptr<sf::Texture> m_backgroundTexture;
		dtn::ProcessManager m_processManager;
		dtn::Tooltip m_tooltip;
		dtn::MovementDecal m_movementDecal;
		sf::Sprite m_background;
		int m_playerID;

		// event listeners
		void initializeListeners();

		void onEntityDrawn(std::shared_ptr<dtn::Event> e);
		void onEntityMoved(std::shared_ptr<dtn::Event> e);
		void onEntityBattle(std::shared_ptr<dtn::Event> e);
		void onEntityAdded(std::shared_ptr<dtn::Event> e);
		void onEntityMoveFlagChanged(std::shared_ptr<dtn::Event> e);

		// old, not in use
		void onAddRenderable(std::shared_ptr<dtn::Event> e);
		void onMoveRenderable(std::shared_ptr<dtn::Event> e);
		void onDeleteRenderable(std::shared_ptr<dtn::Event> e);
		void onUpdateRenderableLos(std::shared_ptr<dtn::Event> e);
		void onUpdateRenderableTooltip(std::shared_ptr<dtn::Event> e);
		void onUpdateRenderableOwner(std::shared_ptr<dtn::Event> e);
	};
}
#endif