#include "gameclient.h"
#include "scenemainmenu.h"
#include<iostream>

#include<SFML/Graphics.hpp>

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(dtn::Utilities::WINDOW_WIDTH, dtn::Utilities::WINDOW_HEIGHT, 32)
		, "Game Client", sf::Style::Default & ~sf::Style::Resize);
	sf::Clock clock;
	sfg::SFGUI sfgui;
	/*
	int pnum;
	std::cout << "ENTER PLAYER NUMBER: ";
	std::cin >> pnum;
	std::string ip;
	std::cout << "ENTER SERVER IP: ";
	std::cin >> ip;
	dtn::GameClient client(pnum, ip);
	client.onAttach();
	while (true)
	{
		float dt = clock.restart().asSeconds();
		client.update(dt, window);
		window.clear();
		client.render(window, sfgui);
		window.display();
	}
	dtn::RunestoneDatabase::getInstance()->generateWriteToFile("names.txt", "condensed_database.csv");
	*/
	dtn::SceneMainMenu mmScene;
	mmScene.onAttach();
	while (true)
	{
		float dt = clock.restart().asSeconds();
		mmScene.update(dt, window);
		window.clear(sf::Color::Black);
		mmScene.render(window, sfgui);
		window.display();
	}
	return 0;
}