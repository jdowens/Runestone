#include "gameclient.h"
#include "scenemainmenu.h"
#include "gameserver.h"
#include "gameclientai.h"
#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

int main()
{
	auto server = std::make_shared<dtn::GameServer>();
	sf::Thread serverInitThread(&dtn::GameServer::initialize, server.get());
	serverInitThread.launch();
	sf::Clock clock;

	sf::RenderWindow p1Win(sf::VideoMode(dtn::Utilities::WINDOW_WIDTH, dtn::Utilities::WINDOW_HEIGHT, 32)
		, "Game Client", sf::Style::Default & ~sf::Style::Resize);
	//sf::RenderWindow p2Win(sf::VideoMode(dtn::Utilities::WINDOW_WIDTH, dtn::Utilities::WINDOW_HEIGHT, 32)
	//	, "Game Client", sf::Style::Default & ~sf::Style::Resize);

	//dtn::SceneManager::getInstance()->runScene(std::shared_ptr<dtn::SceneMainMenu>(
	//	new dtn::SceneMainMenu()));

	dtn::SceneMultiplayerMatch p1(1, "localhost");
	//dtn::SceneMultiplayerMatch p2(2, "localhost");
	p1.onAttach(p1Win);
	//p2.onAttach(p2Win);
	auto aiEventManager = std::make_shared<dtn::EventManager>();
	dtn::GameClientAI ai(2, "localhost", aiEventManager, server);
	ai.connectToServer();

	while (true)
	{
		float dt = clock.restart().asSeconds();
		p1Win.clear();
		//p2Win.clear();
		p1.update(dt, p1Win);
		p1.render(p1Win);
		//p2.update(dt, p2Win);
		//p2.render(p2Win);
		//dtn::SceneManager::getInstance()->update(dt);
		//dtn::SceneManager::getInstance()->render();
		ai.update(dt);
		p1Win.display();
		//p2Win.display();
		server->update();
	}

	dtn::RunestoneDatabase::getInstance()->generateWriteToFile("names.txt", "condensed_database.csv");
	return 0;
}