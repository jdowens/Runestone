#include "gameclient.h"

// constructor
/*
	Sets up a game client class to represent one player's view.
*/
dtn::GameClient::GameClient(int playerID, std::string ip)
	: m_thread(&GameClient::receiveStrings, this)
{
	m_screen = std::shared_ptr<Screen>(new GameScreen(playerID));
	m_hud = std::shared_ptr<HUD>(new HUDgame(playerID));
	m_inputhandler = std::shared_ptr<InputHandler>(new InputHandlerGame(playerID));
	m_screen->loadBackground("Resources/tilemap.png");
	m_screen->moveBackground(sf::Vector2f(dtn::Utilities::BOARD_LEFT*
		dtn::Utilities::PIXELS_PER_TILE_X,
		dtn::Utilities::BOARD_TOP*dtn::Utilities::PIXELS_PER_TILE_Y));
	m_playerID = playerID;

	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::END_TURN,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::RUNESTONE_ATTACK,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::RUNESTONE_MOVE,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::RUNESTONE_PLAY,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::GAME_QUIT,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::REQUEST_ENTITY_MOVE_DECAL,
		std::bind(&GameClient::sendString, this, std::placeholders::_1));

	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::GAME_QUIT,
		std::bind(&GameClient::onGameQuit, this, std::placeholders::_1));
	m_ip = ip;
	m_running = true;
}

void dtn::GameClient::onAttach()
{
	m_socket.connect(m_ip, 5555);
	m_thread.launch();
}

// update
/*
	Called once per loop iteration.
*/
void dtn::GameClient::update(float dt, sf::RenderWindow& window)
{
	// execute pending events
	m_mutex.lock();
	dtn::GlobalEventQueue::getInstance()->update();
	m_mutex.unlock();
	// update game screen
	m_screen->update(dt);
	// handle events
	m_inputhandler->update(window, m_screen, m_hud);
	// update HUD
	m_hud->update(dt);
}

// render
/*
	Called once per loop iteration to draw to the game window.
*/
void dtn::GameClient::render(sf::RenderWindow& target)
{
	m_screen->render(target);
	m_hud->render(target);
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
		dtn::GlobalEventQueue::getInstance()->pushEvent(dtn::Event::stringToEvent(str));
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

// onEntityDrawn
/*
	Callback function for when an entity is drawn to the player's hand.
*/
void dtn::GameClient::onEntityDrawn(std::shared_ptr<dtn::Event> e)
{
	dtn::EventEntityDrawn* cast = dynamic_cast<EventEntityDrawn*>(e.get());
	std::shared_ptr<dtn::Event> rendAdd(new dtn::EventAddRenderable(
		dtn::Utilities::LocalTileToGlobal(cast->source, m_playerID), cast->entityID, cast->renderableID));
	std::shared_ptr<dtn::Event> updateLos(new dtn::EventUpdateRenderableLos(cast->entityID,
		cast->los));
	std::shared_ptr<dtn::Event> updateO(new dtn::EventUpdateRenderableOwner(cast->entityID,
		cast->owner));
	std::shared_ptr<dtn::Event> updateTT(new dtn::EventUpdateRenderableTooltip(cast->entityID,
		cast->tooltip));
	std::shared_ptr<dtn::Event> rendMoved(new dtn::EventMoveRenderable(
		cast->entityID, dtn::Utilities::LocalTileToGlobal(cast->dest, m_playerID), 400.f));
	dtn::GlobalEventQueue::getInstance()->pushEvent(rendAdd);
	dtn::GlobalEventQueue::getInstance()->pushEvent(updateLos);
	dtn::GlobalEventQueue::getInstance()->pushEvent(updateO);
	dtn::GlobalEventQueue::getInstance()->pushEvent(updateTT);
	dtn::GlobalEventQueue::getInstance()->pushEvent(rendMoved);
}

// onEntityMoved
/*
	Callback function for when an entity is moved.
*/
void dtn::GameClient::onEntityMoved(std::shared_ptr<dtn::Event> e)
{
	dtn::EventEntityMoved* cast = dynamic_cast<EventEntityMoved*>(e.get());
	std::shared_ptr<dtn::Event> rendMoved(new dtn::EventMoveRenderable(
		cast->entityID, dtn::Utilities::LocalTileToGlobal(cast->dest, m_playerID), 200.f));
	std::shared_ptr<dtn::Event> updateTT(new dtn::EventUpdateRenderableTooltip(cast->entityID,
		cast->tooltip));
	dtn::GlobalEventQueue::getInstance()->pushEvent(rendMoved);
	dtn::GlobalEventQueue::getInstance()->pushEvent(updateTT);
}

// onEntityBattle
/*
	Callback function for when an entity is battled.
*/
void dtn::GameClient::onEntityBattle(std::shared_ptr<dtn::Event> e)
{
	EventEntityBattle* cast = dynamic_cast<EventEntityBattle*>(e.get());
	std::shared_ptr<dtn::Event> updateTT1(new dtn::EventUpdateRenderableTooltip(
		cast->attackerEntityID,
		cast->tooltipAttacker));
	std::shared_ptr<dtn::Event> updateTT2(new dtn::EventUpdateRenderableTooltip(
		cast->defenderEntityID,
		cast->tooltipDefender));
	dtn::GlobalEventQueue::getInstance()->pushEvent(updateTT1);
	dtn::GlobalEventQueue::getInstance()->pushEvent(updateTT2);
	if (cast->attackerDead)
	{
		std::shared_ptr<dtn::Event> deleteRen(new dtn::EventDeleteRenderable(cast->attackerEntityID));
		dtn::GlobalEventQueue::getInstance()->pushEvent(deleteRen);
	}
	if (cast->defenderDead)
	{
		std::shared_ptr<dtn::Event> deleteRen(new dtn::EventDeleteRenderable(cast->defenderEntityID));
		dtn::GlobalEventQueue::getInstance()->pushEvent(deleteRen);
	}
}

// onEntityAdded
/*
	Callback function for when an entity is played to the battlefield.
*/
void dtn::GameClient::onEntityAdded(std::shared_ptr<dtn::Event> e)
{
	EventEntityAdded* cast = dynamic_cast<EventEntityAdded*>(e.get());
	std::shared_ptr<dtn::Event> rendAdd(new dtn::EventAddRenderable(
		dtn::Utilities::LocalBoundsToGlobalPosition(cast->bounds, m_playerID), cast->entityID, cast->renderableID));
	std::shared_ptr<dtn::Event> updateLos(new dtn::EventUpdateRenderableLos(cast->entityID,
		cast->los));
	std::shared_ptr<dtn::Event> updateO(new dtn::EventUpdateRenderableOwner(cast->entityID,
		cast->owner));
	std::shared_ptr<dtn::Event> updateTT(new dtn::EventUpdateRenderableTooltip(cast->entityID,
		cast->tooltip));
	dtn::GlobalEventQueue::getInstance()->pushEvent(rendAdd);
	dtn::GlobalEventQueue::getInstance()->pushEvent(updateLos);
	dtn::GlobalEventQueue::getInstance()->pushEvent(updateO);
	dtn::GlobalEventQueue::getInstance()->pushEvent(updateTT);
}

// onGameQuit
/*
Callback function for when a player has requested to quit the game
*/
void dtn::GameClient::onGameQuit(std::shared_ptr<dtn::Event> e) 
{
	m_running = false;
}