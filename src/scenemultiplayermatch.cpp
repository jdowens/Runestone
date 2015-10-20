#include "scenemultiplayermatch.h"

dtn::SceneMultiplayerMatch::SceneMultiplayerMatch(int playerID, std::string ip)
{
	m_playerID = playerID;
	m_eventManager = std::make_shared<EventManager>();
	m_client = std::make_shared<GameClient>(playerID, ip, m_eventManager);
	m_screen = std::shared_ptr<Screen>(new GameScreen(playerID, m_eventManager));
	m_inputhandler = std::shared_ptr<InputHandler>(new InputHandlerGame(playerID, m_eventManager));
	m_screen->loadBackground("Resources/tilemap.png");
	m_screen->moveBackground(sf::Vector2f(dtn::Utilities::BOARD_LEFT*
		dtn::Utilities::PIXELS_PER_TILE_X,
		dtn::Utilities::BOARD_TOP*dtn::Utilities::PIXELS_PER_TILE_Y));
}

void dtn::SceneMultiplayerMatch::onAttach(sf::RenderWindow & dest)
{
	m_hud = std::shared_ptr<HUD>(new HUDgame(m_playerID, dest, m_eventManager));
	m_client->connectToServer();
}

void dtn::SceneMultiplayerMatch::update(float dt, sf::RenderWindow & window)
{
	// update game screen
	m_screen->update(dt);
	// handle events
	m_inputhandler->update(window, m_screen, m_hud);
	// update HUD
	m_hud->update(dt);
	// update communication
	m_client->update(dt);
}

void dtn::SceneMultiplayerMatch::render(sf::RenderWindow & target)
{
	m_screen->render(target);
	m_hud->render(target);
}
