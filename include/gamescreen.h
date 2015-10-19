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
#include "losdecal.h"
#include "screen.h"

namespace dtn
{
	class GameScreen : public Screen
	{
		friend class InputHandlerGame;
	public :
		// constructors
		GameScreen(int playerID);

		// update function (called once per global loop)
		virtual void update(float dt);

		// render to window
		virtual void render(sf::RenderWindow& window);
		
		// handle the addition/removal of renderables
		void pushRenderable(int entityID, std::shared_ptr<dtn::Renderable> renderable);
		void removeRenderable(int entityID);

		// get renderable at a pixel position
		std::shared_ptr<dtn::Renderable> getRenderableAt(sf::Vector2i position);
		std::shared_ptr<dtn::Renderable> getRenderableAt(sf::Vector2f position);
	private :
		std::map<int, std::shared_ptr<dtn::Renderable>> m_renderables;
		dtn::Tooltip m_tooltip;
		dtn::MovementDecal m_movementDecal;
		dtn::LOSDecal m_LOSDecal;
		int m_playerID;

		// event listeners
		void initializeListeners();

		void onEntityDrawn(std::shared_ptr<dtn::Event> e);
		void onEntityMoved(std::shared_ptr<dtn::Event> e);
		void onEntityBattle(std::shared_ptr<dtn::Event> e);
		void onEntityAdded(std::shared_ptr<dtn::Event> e);
		void onEntityMoveFlagChanged(std::shared_ptr<dtn::Event> e);
		void onReceivedEntityMoveDecal(std::shared_ptr<dtn::Event> e);
		void onReceivedBoardLOSDecal(std::shared_ptr<dtn::Event> e);
		void onDeleteRenderable(std::shared_ptr<dtn::Event> e);

		// old, not in use
		void onAddRenderable(std::shared_ptr<dtn::Event> e);
		void onMoveRenderable(std::shared_ptr<dtn::Event> e);
		void onUpdateRenderableLos(std::shared_ptr<dtn::Event> e);
		void onUpdateRenderableTooltip(std::shared_ptr<dtn::Event> e);
		void onUpdateRenderableOwner(std::shared_ptr<dtn::Event> e);
	};
}
#endif