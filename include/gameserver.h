/*
	gameserver.h
	Abstraction for a game server. Sends/receives events from two separate player clients.
*/

#ifndef _SERVER_H
#define _SERVER_H

// c++ includes
#include<memory>
#include<vector>

// sfml includes
#include<SFML/Network.hpp>
#include<SFML/System.hpp>

// dtn includes
#include "eventmanager.h"
#include "event.h"
#include "player.h"
#include "battlefield.h"
#include "globaleventqueue.h"

namespace dtn
{
	class GameServer
	{
	public :
		// constructor
		GameServer();

		// main run function
		void run();

		// called once per loop iteration
		void update();
	private :
		bool m_running;										// true if both players are connected, false if one quits
		std::vector<dtn::Player> m_players;					// two players
		int m_currentPlayer;								// number of players
		int m_turnCount;									// which turn the server is on
		dtn::Battlefield m_battlefield;						// the battlefield to play runestones to
		void draw(int playerID);							// make a player draw a runestone
		void initializeBases();								// initialize the player's keeps
		std::vector<sf::Vector2i> m_deckPositions;			// where the player's decks are located

		// update LOS function
		void updateLOS(int playerID);

		// update player hand
		// the player id is the player who just played a card
		void updatePlayerHand(int playerID);

		sf::Thread m_thread1, m_thread2;					// dual player comm features
		sf::Mutex m_mutex1, m_mutex2;
		sf::TcpSocket m_p1Socket, m_p2Socket;
		sf::TcpListener m_listener;
		void p1Com();										// receive channel 1
		void p2Com();										// receive channel 2
		void sendCom(std::shared_ptr<dtn::Event> e);		// send channel (global)
		void sendP1Com(std::shared_ptr<dtn::Event> e);		// send channel p1 only
		void sendP2Com(std::shared_ptr<dtn::Event> e);		// send channel p2 only

		dtn::EventManager m_sendEventManager;						// dual event managers (to handle sent/received events)
		dtn::EventManager m_receiveEventManager;
			
		dtn::EventManager m_exclusiveP1SendManager;					// single channel send managers
		dtn::EventManager m_exclusiveP2SendManager;

		// listeners
		void onEndTurn(std::shared_ptr<dtn::Event> e);
		void onRunestoneMove(std::shared_ptr<dtn::Event> e);
		void onRunestonePlay(std::shared_ptr<dtn::Event> e);
		void onRunestoneAttack(std::shared_ptr<dtn::Event> e);
		void onPlayerQuit(std::shared_ptr<dtn::Event> e);
		void onRequestEntityMoveDecal(std::shared_ptr<dtn::Event> e);

		// internal listeners
		void onManaChanged(std::shared_ptr<dtn::Event> e);
		void onEntityMoveFlagChanged(std::shared_ptr<dtn::Event> e);
	};
}

#endif