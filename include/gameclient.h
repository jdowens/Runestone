/*
	gameclient.h
	A class that holds all logic to provide an interface to a client.
*/

#ifndef _GAMECLIENT_H
#define _GAMECLIENT_H

// c++ includes
#include<memory>
#include<vector>

// SFML includes
#include<SFML/Network.hpp>
#include<SFML/System.hpp>

// dtn includes
#include"globaleventqueue.h"
#include "event.h"
#include "gamescreen.h"
#include "inputhandlergame.h"
#include "HUD.h"
#include "HUDgame.h"
#include "scene.h"

namespace dtn
{
	class GameClient
	{
	public :
		// constructor
		GameClient(int playerID, std::string ip, std::shared_ptr<EventManager> eventManager);
		
		// on attach
		void connectToServer();

		// update (one loop iteration)
		 void update(float dt);
	private :

		// TCP communication function (receive)
		void receiveStrings();

		// TCP communication function (send)
		void sendString(std::shared_ptr<dtn::Event> e);
		
		// data
		int m_playerID;											// player identification number
		sf::TcpSocket m_socket;									// socket for TCP comm
		sf::Mutex m_mutex;										// global mutex (for dual thread communication)
		sf::Thread m_thread;									// one thread used to receive data asynchronously
		std::string m_ip;										// the ip address of the server
		std::shared_ptr<EventManager> m_eventManager;			// event manager for communication

		// listeners
		void onGameQuit(std::shared_ptr<dtn::Event> e);
	};
}

#endif