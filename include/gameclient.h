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
#include "inputhandler.h"

namespace dtn
{
	class GameClient
	{
	public :
		// constructor
		GameClient(int playerID, std::string ip);

		// run (main loop)
		void run();
		
		// update (one loop iteration)
		void update();
	private :
		// render function
		void render();											// called each loop to render to screen
		
		// TCP communication function (receive)
		void receiveStrings();

		// TCP communication function (send)
		void sendString(std::shared_ptr<dtn::Event> e);
		
		// data
		GameScreen m_screen;									// graphics portion
		InputHandler m_inputhandler;							// all input handled here
		sf::RenderWindow m_window;								// game window
		sf::Clock m_clock;										// client clock	
		int m_playerID;											// player identification number
		sf::TcpSocket m_socket;									// socket for TCP comm
		sf::Mutex m_mutex;										// global mutex (for dual thread communication)
		sf::Thread m_thread;									// one thread used to receive data asynchronously
		std::string m_ip;										// the ip address of the server
		bool m_running;											// flag for whether or not a player has quit the game
																
		// listeners
		void onEntityDrawn(std::shared_ptr<dtn::Event> e);
		void onEntityMoved(std::shared_ptr<dtn::Event> e);
		void onEntityBattle(std::shared_ptr<dtn::Event> e);
		void onEntityAdded(std::shared_ptr<dtn::Event> e);
		void onGameQuit(std::shared_ptr<dtn::Event> e);
	};
}

#endif