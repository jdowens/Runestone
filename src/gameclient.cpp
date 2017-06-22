#include "gameclient.h"

// constructor
/*
	Sets up a game client class to represent one player's view.
*/
dtn::GameClient::GameClient(int playerID, std::string ip, std::shared_ptr<EventManager> eventManager)
	: m_thread(&GameClient::receiveStrings, this)
{
	m_playerID = playerID;
	m_eventManager = eventManager;
	m_eventManager->attachListener(dtn::Event::EventType::END_TURN,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));
	m_eventManager->attachListener(dtn::Event::EventType::RUNESTONE_ATTACK,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));
	m_eventManager->attachListener(dtn::Event::EventType::RUNESTONE_MOVE,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));
	m_eventManager->attachListener(dtn::Event::EventType::RUNESTONE_PLAY,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));
	m_eventManager->attachListener(dtn::Event::EventType::GAME_QUIT,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));
	m_eventManager->attachListener(dtn::Event::EventType::REQUEST_ENTITY_MOVE_DECAL,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));

	m_eventManager->attachListener(dtn::Event::EventType::GAME_QUIT,
		std::bind(&GameClient::onGameQuit, this, std::placeholders::_1));
	m_ip = ip;
}

void dtn::GameClient::connectToServer()
{
	m_socket.connect(m_ip, 5555);
	m_thread.launch();
}

// update
/*
	Called once per loop iteration.
*/
void dtn::GameClient::update(float dt)
{
	// execute pending events
	m_mutex.lock();
	m_eventManager->update();
	m_mutex.unlock();
}

// receiveStrings
/*
	Serial communcation function run in m_thread to asynchronously receive packets from server.
*/
void dtn::GameClient::receiveStrings()
{
	std::string str;
	while (true)
	{
		sf::Packet packet;
		if (m_socket.receive(packet) !=
			sf::Socket::Done)
		{
			std::cout << "Receive not done!\n";
		};
		str.clear();
		packet >> str;
		std::cout << str << '\n';
		m_mutex.lock();
		m_eventManager->pushEvent(dtn::Event::stringToEvent(str));
		m_mutex.unlock();
	}
}

// sendString
/*
	This function subscribes to all action events from the inputhandler class. It sends the events over
	serial comm to the server.
*/
void dtn::GameClient::sendString(std::shared_ptr<dtn::Event> e)
{
	sf::Packet packet;
	std::string str = e->toString();
	std::size_t t = str.length();
	packet << str;
	m_socket.send(packet);
}

// onGameQuit
/*
Callback function for when a player has requested to quit the game
*/
void dtn::GameClient::onGameQuit(std::shared_ptr<dtn::Event> e) 
{

}