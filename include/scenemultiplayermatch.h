#ifndef _SCENE_MULTIPLAYER_MATCH_H
#define _SCENE_MULTIPLAYER_MATCH_H

#include "scene.h"
#include "inputhandlergame.h"
#include "HUDgame.h"
#include "gameclient.h"

namespace dtn
{
	class SceneMultiplayerMatch : public Scene
	{
	public :
		// constructor
		SceneMultiplayerMatch(int playerID, std::string ip);

		// on attach
		virtual void onAttach(sf::RenderWindow& dest);

		// update (one loop iteration)
		virtual void update(float dt, sf::RenderWindow& window);

		// render function
		virtual void render(sf::RenderWindow& target);
	private :
		int m_playerID;
		std::shared_ptr<GameClient> m_client;
	};
}

#endif