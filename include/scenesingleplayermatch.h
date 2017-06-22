#ifndef _SCENE_SINGLEPLAYER_MATCH_H
#define _SCENE_SINGLEPLAYER_MATCH_H

#include "scene.h"
#include "inputhandlergame.h"
#include "HUDgame.h"
#include "gameclient.h"
#include "gameserver.h"
#include "gameclientai.h"

namespace dtn
{
	class SceneSingleplayerMatch : public Scene
	{
	public:
		// constructor
		SceneSingleplayerMatch();

		// on attach
		virtual void onAttach(sf::RenderWindow& dest);

		// update (one loop iteration)
		virtual void update(float dt, sf::RenderWindow& window);

		// render function
		virtual void render(sf::RenderWindow& target);
	private:
		int m_playerID;
		std::shared_ptr<GameClient> m_client;
		std::shared_ptr<GameServer> m_server;
		std::shared_ptr<GameClientAI> m_aiClient;
		std::shared_ptr<EventManager> m_aiEventManager;
	};
}

#endif