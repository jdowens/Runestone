#ifndef _GAME_CLIENT_AI_H
#define _GAME_CLIENT_AI_H

#include<algorithm>
#include<vector>

#include "gameclient.h"
#include "eventmanager.h"
#include "gameserver.h"

namespace dtn
{
	class GameClientAI : public GameClient
	{
	public :
		// constructor
		GameClientAI(int playerID, std::string ip, std::shared_ptr<EventManager> eventManager,
			std::shared_ptr<GameServer> serverRef);
		virtual void update(float dt);
	private :
		std::shared_ptr<GameServer> m_serverRef;
		float m_timeBetweenActions;
		float m_currentTime;
		int m_currentStep;
		// run one action
		void step();
		void playOutHand();
		void moveAllPieces();
		void attackInRange();
	};
}

#endif