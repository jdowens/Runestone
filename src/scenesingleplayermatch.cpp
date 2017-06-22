#include "..\include\scenesingleplayermatch.h"

dtn::SceneSingleplayerMatch::SceneSingleplayerMatch()
{
	m_server = std::make_shared<dtn::GameServer>();

	m_eventManager = std::make_shared<EventManager>();
	m_client = std::make_shared<GameClient>(1, "localhost", m_eventManager);
	m_screen = std::shared_ptr<Screen>(new GameScreen(1, m_eventManager));
	m_inputhandler = std::shared_ptr<InputHandler>(new InputHandlerGame(1, m_eventManager));
	m_screen->loadBackground("Resources/tilemap.png");
	m_screen->moveBackground(sf::Vector2f(dtn::Utilities::BOARD_LEFT*
		dtn::Utilities::PIXELS_PER_TILE_X,
		dtn::Utilities::BOARD_TOP*dtn::Utilities::PIXELS_PER_TILE_Y));
	m_aiEventManager = std::make_shared<EventManager>();
	m_aiClient = std::make_shared<dtn::GameClientAI>(2, "localhost", m_aiEventManager, m_server);
}

void dtn::SceneSingleplayerMatch::onAttach(sf::RenderWindow & dest)
{
	m_hud = std::shared_ptr<HUD>(new HUDgame(1, dest, m_eventManager));
	sf::Thread serverInitThread(&dtn::GameServer::initialize, m_server.get());
	serverInitThread.launch();
	m_client->connectToServer();
	m_aiClient->connectToServer();
}

void dtn::SceneSingleplayerMatch::update(float dt, sf::RenderWindow & window)
{
	// update game screen
	m_screen->update(dt);
	// handle events
	m_inputhandler->update(window, m_screen, m_hud);
	// update HUD
	m_hud->update(dt);
	// update communication
	m_client->update(dt);
	// update ai
	m_aiClient->update(dt);
	// update server
	m_server->update();
}

void dtn::SceneSingleplayerMatch::render(sf::RenderWindow & target)
{
	m_screen->render(target);
	m_hud->render(target);
}
