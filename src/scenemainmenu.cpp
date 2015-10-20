#include "scenemainmenu.h"

dtn::SceneMainMenu::SceneMainMenu()
{
	m_inputhandler = NULL;
	m_screen = NULL;
}

void dtn::SceneMainMenu::onAttach(sf::RenderWindow& dest)
{
	m_hud = std::shared_ptr<HUD>(new HUDMainMenu(dest));
}

void dtn::SceneMainMenu::update(float dt, sf::RenderWindow & window)
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		m_hud->handleEvent(e);
		if (e.type == sf::Event::Closed)
			window.close();
	}
	m_hud->update(dt);
}

void dtn::SceneMainMenu::render(sf::RenderWindow & target)
{
	m_hud->render(target);
}