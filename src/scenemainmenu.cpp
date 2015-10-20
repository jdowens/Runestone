#include "scenemainmenu.h"

dtn::SceneMainMenu::SceneMainMenu()
{
	m_inputhandler = NULL;
	m_screen = NULL;
}

void dtn::SceneMainMenu::onAttach()
{
	m_hud = std::shared_ptr<HUD>(new HUDMainMenu());
}

void dtn::SceneMainMenu::update(float dt, sf::RenderWindow & window)
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		m_hud->handleEvent(e);
	}
	m_hud->update(dt);
}

void dtn::SceneMainMenu::render(sf::RenderWindow & target)
{
	m_hud->render(target);
}