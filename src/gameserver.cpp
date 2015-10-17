#include "gameserver.h"

// constructor
/*
	Sets up a default game server to handle 2 players. 
*/
dtn::GameServer::GameServer()
	: m_battlefield(sf::Vector2i(dtn::Utilities::BOARD_WIDTH, dtn::Utilities::BOARD_HEIGHT)),
	m_thread1(&GameServer::p1Com, this), m_thread2(&GameServer::p2Com, this)
{
	// create two players and load default deck lists
	dtn::Player p1(1), p2(2);
	p1.loadDeckFromFile("Resources/p1deck.txt");
	p2.loadDeckFromFile("Resources/p2deck.txt");
	m_players.push_back(p1);
	m_players.push_back(p2);
	// initialize current player
	m_currentPlayer = 1;
	m_turnCount = 0;
	// setup where the player's decks are located (this should be moved)
	m_deckPositions.push_back(sf::Vector2i(dtn::Utilities::BOARD_LEFT + dtn::Utilities::BOARD_WIDTH + 1,
		dtn::Utilities::BOARD_TOP + dtn::Utilities::BOARD_HEIGHT - 1));
	m_deckPositions.push_back(sf::Vector2i(dtn::Utilities::BOARD_LEFT + dtn::Utilities::BOARD_WIDTH + 1,
		dtn::Utilities::BOARD_TOP));

	// register listeners

	// send
	m_sendEventManager.attachListener(dtn::Event::EventType::ALL_EVENTS,
		std::bind(&GameServer::sendCom, this, std::placeholders::_1));

	// receive
	m_receiveEventManager.attachListener(dtn::Event::EventType::END_TURN,
		std::bind(&GameServer::onEndTurn, this, std::placeholders::_1));
	m_receiveEventManager.attachListener(dtn::Event::EventType::RUNESTONE_ATTACK,
		std::bind(&GameServer::onRunestoneAttack, this, std::placeholders::_1));
	m_receiveEventManager.attachListener(dtn::Event::EventType::RUNESTONE_MOVE,
		std::bind(&GameServer::onRunestoneMove, this, std::placeholders::_1));
	m_receiveEventManager.attachListener(dtn::Event::EventType::RUNESTONE_PLAY,
		std::bind(&GameServer::onRunestonePlay, this, std::placeholders::_1));
	m_receiveEventManager.attachListener(dtn::Event::EventType::GAME_QUIT,
		std::bind(&GameServer::onPlayerQuit, this, std::placeholders::_1));

	// listener for internal server events (to send to clients)
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::MANA_CHANGED,
		std::bind(&GameServer::onManaChanged, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_MOVE_FLAG_CHANGED,
		std::bind(&GameServer::onEntityMoveFlagChanged, this, std::placeholders::_1));

	m_running = true;
}

// run
/*
	Run the game server.
*/
void dtn::GameServer::run()
{
	// listen on port 5555 and accept two connections
	m_listener.listen(5555);
	m_listener.accept(m_p1Socket);
	m_listener.accept(m_p2Socket);
	// launch two threads
	m_thread1.launch();
	m_thread2.launch();
	// run main loop
	while (m_running)
	{
		m_mutex1.lock();
		m_mutex2.lock();
		update();
		m_mutex2.unlock();
		m_mutex1.unlock();
	}
	// finish sending events before quiting
	if (m_sendEventManager.pendingEvents())
	{
		m_sendEventManager.update();
	}
	m_thread1.terminate();
	m_thread2.terminate();
}

// update
/*
	Called once per loop iteration.
*/
void dtn::GameServer::update()
{
	m_receiveEventManager.update();
	m_battlefield.update();
	// on turn 0, each player draws three runestones, and player 1 gets 
	// a mana token
	if (m_turnCount == 0)
	{
		draw(1); draw(1); draw(1); draw(2); draw(2); draw(2);
		m_players[0].increaseMana();
		m_players[0].resetCurrentMana();
		initializeBases();
		m_turnCount++;
	}
	// shift any internal events to the send queue
	dtn::GlobalEventQueue::getInstance()->update();
	// send the waiting events
	m_sendEventManager.update();
}

// event listeners below
void dtn::GameServer::onEndTurn(std::shared_ptr<dtn::Event> e)
{
	m_currentPlayer = m_currentPlayer == 1 ? 2 : 1;
	draw(m_currentPlayer); m_battlefield.resetEntityBattlefieldFlags();
	m_players[m_currentPlayer - 1].increaseMana();
	m_players[m_currentPlayer - 1].resetCurrentMana();
	m_turnCount++;
}

void dtn::GameServer::onRunestoneMove(std::shared_ptr<dtn::Event> e)
{
	EventRunestoneMove* cast = dynamic_cast<EventRunestoneMove*>(e.get());
	if (m_players[m_currentPlayer - 1].moveRunestone(cast->source, cast->dest,
		m_battlefield))
	{
		std::shared_ptr<dtn::EntityBattlefield> rune =
			m_battlefield.getEntityBattlefieldAt(cast->dest);
		// an entity has moved
		m_sendEventManager.pushEvent(std::shared_ptr<dtn::Event>(
			new dtn::EventEntityMoved(rune->getEntityID(), cast->dest, rune->toString())));
	}
}

void dtn::GameServer::onRunestonePlay(std::shared_ptr<dtn::Event> e)
{
	EventRunestonePlay* cast = dynamic_cast<EventRunestonePlay*>(e.get());
	if (m_players[m_currentPlayer - 1].playRunestone(cast->entityID,
		cast->dest, m_battlefield))
	{
		std::shared_ptr<dtn::EntityBattlefield> rune =
			m_battlefield.getEntityBattlefieldAt(cast->dest);
		// an entity has moved
		m_sendEventManager.pushEvent(std::shared_ptr<dtn::Event>(
			new dtn::EventEntityMoved(rune->getEntityID(), cast->dest, rune->toString())));

		std::vector<std::shared_ptr<dtn::Runestone>> vec =
			m_players[m_currentPlayer - 1].getHand();
		int count = 1;
		for (std::vector<std::shared_ptr<dtn::Runestone>>::iterator it = vec.begin();
			it != vec.end(); ++it)
		{
			m_sendEventManager.pushEvent(std::shared_ptr<dtn::Event>(
				new dtn::EventEntityMoved((*it)->getEntityID(), 
				m_players[m_currentPlayer - 1].getHandPosition(count++), 
				(*it)->toString())));
		}
	}
}

void dtn::GameServer::onRunestoneAttack(std::shared_ptr<dtn::Event> e)
{
	EventRunestoneAttack* cast = dynamic_cast<EventRunestoneAttack*>(e.get());
	if (m_players[m_currentPlayer - 1].attackRunestone(cast->source,
		cast->dest, m_battlefield))
	{
		std::shared_ptr<dtn::EntityBattlefield> rune1 =
			m_battlefield.getEntityBattlefieldAt(cast->source);
		std::shared_ptr<dtn::EntityBattlefield> rune2 =
			m_battlefield.getEntityBattlefieldAt(cast->dest);

		m_sendEventManager.pushEvent(std::shared_ptr<dtn::Event>(
			new dtn::EventEntityBattle(rune1->getEntityID(), rune2->getEntityID(), rune1->toString(),
			rune2->toString(), rune1->isDead(), rune2->isDead())));

		// if rune2 was a playerbase and it died, the game is over
		if (rune2->getType() == dtn::Entity::EntityType::PLAYERBASE &&
			rune2->isDead())
		{
			m_sendEventManager.pushEvent(std::shared_ptr<dtn::Event>(
				new dtn::EventGameQuit()));
		}
	}
}

void dtn::GameServer::onPlayerQuit(std::shared_ptr<dtn::Event> e)
{
	m_running = false;
}

void dtn::GameServer::onManaChanged(std::shared_ptr<dtn::Event> e)
{
	// hand it over to the send channel
	m_sendEventManager.pushEvent(e);
}

void dtn::GameServer::onEntityMoveFlagChanged(std::shared_ptr<dtn::Event> e)
{
	m_sendEventManager.pushEvent(e);
}

// draw
/*
	Makes a player draw a runestone.
	Sends an event to each client.
*/
void dtn::GameServer::draw(int playerID)
{
	if (m_players[playerID - 1].draw())
	{
		std::shared_ptr<dtn::Runestone> rune = m_players[playerID - 1].getLastDrawn();
		m_sendEventManager.pushEvent(std::shared_ptr<dtn::Event>(new dtn::EventEntityDrawn(
			rune->getEntityID(), rune->getOwner(), rune->getLos(),
			rune->toString(), m_deckPositions[playerID-1], 
			m_players[playerID - 1].getHandPosition(),rune->getRenderableID())));
	}
}

// initializeBases
/*
	Setup the two keeps on the battlefield.
*/
void dtn::GameServer::initializeBases()
{
	// TEMPORARY
	std::shared_ptr<dtn::PlayerBase> p1q1 = std::shared_ptr<dtn::PlayerBase>(new dtn::PlayerBase(
		1, sf::Vector2i(dtn::Utilities::BOARD_LEFT + dtn::Utilities::BOARD_WIDTH / 2 - 1,
		dtn::Utilities::BOARD_TOP + dtn::Utilities::BOARD_HEIGHT - 4)));

	std::shared_ptr<dtn::PlayerBase> p2q1 = std::shared_ptr<dtn::PlayerBase>(new dtn::PlayerBase(
		2, sf::Vector2i(dtn::Utilities::BOARD_LEFT + dtn::Utilities::BOARD_WIDTH / 2 - 1,
		dtn::Utilities::BOARD_TOP + 2)));

	m_battlefield.playEntityBattlefield(p1q1, p1q1->getTilePos());
	std::shared_ptr<dtn::Event> e1(new dtn::EventEntityAdded(
		p1q1->getEntityID(), p1q1->getOwner(), p1q1->getLos(),
		p1q1->toString(), p1q1->getBounds(), p1q1->getRenderableID()));
	m_sendEventManager.pushEvent(e1);

	m_battlefield.playEntityBattlefield(p2q1, p2q1->getTilePos());
	std::shared_ptr<dtn::Event> e5(new dtn::EventEntityAdded(
		p2q1->getEntityID(), p2q1->getOwner(), p2q1->getLos(),
		p2q1->toString(), p2q1->getBounds(), p2q1->getRenderableID()));
	m_sendEventManager.pushEvent(e5);
}

// p1Com
/*
	Receive events from player 1.
*/
void dtn::GameServer::p1Com()
{
	std::string str;
	while (true)
	{
		sf::Packet packet;
		if (m_p1Socket.receive(packet) !=
			sf::Socket::Done)
		{
			std::cout << "Server didn't finish receiving p1com!\n";
		}
		str.clear();
		packet >> str;
		std::cout << str << '\n';
		m_mutex1.lock();
		if (m_currentPlayer == 1)
			m_receiveEventManager.pushEvent(dtn::Event::stringToEvent(str));
		m_mutex1.unlock();
	}
}

// p2Com
/*
	Receive events from player 2.
*/
void dtn::GameServer::p2Com()
{
	std::string str;
	while (true)
	{
		sf::Packet packet;
		if (m_p2Socket.receive(packet) !=
			sf::Socket::Done)
		{
			std::cout << "Server didn't finish receiving p2com!\n";
		}
		str.clear();
		packet >> str;
		std::cout << str << '\n';
		m_mutex2.lock();
		if (m_currentPlayer == 2)
			m_receiveEventManager.pushEvent(dtn::Event::stringToEvent(str));
		m_mutex2.unlock();
	}
}

// sendCom
/*
	Communicate game logic events to each client.
*/
void dtn::GameServer::sendCom(std::shared_ptr<dtn::Event> e)
{
	sf::Packet packet;
	std::string str = e->toString();
	std::cout << str.c_str() << '\n';
	packet << str;
	m_p1Socket.send(packet);
	m_p2Socket.send(packet);
}