#include "gameclient.h"
#include "scenemainmenu.h"
#include "gameserver.h"
#include "gameclientai.h"
#include "scenesingleplayermatch.h"
#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

int main()
{
	sf::Clock clock;
	dtn::SceneManager::getInstance()->runScene(std::shared_ptr<dtn::SceneMainMenu>(
		new dtn::SceneMainMenu()));

	while (true)
	{
		float dt = clock.restart().asSeconds();
		dtn::SceneManager::getInstance()->update(dt);
		dtn::SceneManager::getInstance()->render();
	}

	dtn::RunestoneDatabase::getInstance()->generateWriteToFile("names.txt", "condensed_database.csv");
	return 0;
}