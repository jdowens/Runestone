#include "gameclient.h"
#include "scenemainmenu.h"
#include "gameserver.h"
#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

int main()
{

	//dtn::GameServer server;
	//sf::Thread serverInitThread(&dtn::GameServer::initialize, &server);
	//serverInitThread.launch();
	sf::Clock clock;

	//sf::RenderWindow p1Win(sf::VideoMode(dtn::Utilities::WINDOW_WIDTH, dtn::Utilities::WINDOW_HEIGHT, 32)
	//	, "Game Client", sf::Style::Default & ~sf::Style::Resize);
	//sf::RenderWindow p2Win(sf::VideoMode(dtn::Utilities::WINDOW_WIDTH, dtn::Utilities::WINDOW_HEIGHT, 32)
	//	, "Game Client", sf::Style::Default & ~sf::Style::Resize);
	dtn::SceneManager::getInstance()->runScene(std::shared_ptr<dtn::SceneMainMenu>(
		new dtn::SceneMainMenu()));
	//dtn::GameClient p1(1, "localhost");
	//dtn::GameClient p2(2, "localhost");
	//p1.onAttach(p1Win);
	//p2.onAttach(p2Win);

	while (true)
	{
		float dt = clock.restart().asSeconds();
		//p1.update(dt, p1Win);
		//p1.render(p2Win);
		//p2.update(dt, p2Win);
		//p2.render(p2Win);
		dtn::SceneManager::getInstance()->update(dt);
		dtn::SceneManager::getInstance()->render();
		//server.update();
	}

	dtn::RunestoneDatabase::getInstance()->generateWriteToFile("names.txt", "condensed_database.csv");
	return 0;
}