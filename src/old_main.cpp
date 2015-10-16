//#include<iostream>
//#include<memory>
//#include<SFML/Graphics.hpp>
//#include<SFML/System.hpp>
//#include<SFML/Window.hpp>
//#include<vector>
//#include "runestone.h"
//#include "runestonedatabase.h"
//#include "processmanager.h"
//#include "process.h"
//#include "processmove.h"
//#include "battlefield.h"
//#include "tooltip.h"
//#include "playerhand.h"
//#include "player.h"
//
//sf::RenderWindow window(sf::VideoMode(1024, 768, 32), "P1");
//sf::RenderWindow window2(sf::VideoMode(1024, 768, 32), "P2");
//sf::Vector2i mousePos(0, 0);
//std::vector<std::shared_ptr<dtn::Runestone>> runes;
//dtn::ProcessManager processManager;
//dtn::Battlefield battlefield(sf::Vector2i(16, 16));
//sf::Clock globalClock;
//dtn::Tooltip tooltip;
//std::shared_ptr<dtn::Runestone> hovered;
//std::shared_ptr<dtn::Runestone> selected;
//sf::Texture backgroundTexture;
//sf::Sprite backgroundSprite;
//dtn::Player p1(1), p2(2);
//int currentPlayer = 1;
//
//void Setup()
//{
//	runes.push_back(dtn::RunestoneDatabase::getInstance()->newRunestone(0));
//	runes.push_back(dtn::RunestoneDatabase::getInstance()->newRunestone(1));
//	runes.push_back(dtn::RunestoneDatabase::getInstance()->newRunestone(0));
//	runes.push_back(dtn::RunestoneDatabase::getInstance()->newRunestone(1));
//	p1.addToDeck(runes[0]);
//	p1.addToDeck(runes[1]);
//	p2.addToDeck(runes[2]);
//	p2.addToDeck(runes[3]);
//	backgroundTexture.loadFromFile("resources/grid.png");
//	backgroundSprite.setTexture(backgroundTexture);
//	backgroundSprite.setPosition(sf::Vector2f(
//		static_cast<float>(dtn::PIXELS_PER_TILE),
//		static_cast<float>(dtn::PIXELS_PER_TILE)));
//	globalClock.restart();
//}
//
//void UpdateHovered()
//{
//	if (currentPlayer == 1)
//	{
//		if (mousePos.y < dtn::PIXELS_PER_TILE)
//		{
//			hovered = p1.getRunestoneAt(mousePos);
//		}
//		else
//		{
//			if (battlefield.isVisible(mousePos, 1));
//			{
//				hovered = battlefield.getRunestoneAt(mousePos);
//			}
//		}
//	}
//	else if (currentPlayer == 2)
//	{
//		if (mousePos.y > dtn::PIXELS_PER_TILE * 17)
//		{
//			hovered = p2.getRunestoneAt(mousePos);
//		}
//		else
//		{
//			if (battlefield.isVisible(mousePos, 2))
//			{
//				hovered = battlefield.getRunestoneAt(mousePos);
//			}
//		}
//	}
//	if (hovered != NULL)
//	{
//		tooltip.setVisible();
//		tooltip.setText(hovered->toString());
//		tooltip.setLocation(mousePos);
//	}
//	else
//	{
//		tooltip.setInvisible();
//	}
//}
//
//void HandleEvent(sf::Event event)
//{
//	if (event.type == sf::Event::Closed)
//	{
//		window.close();
//	}
//	else if (event.type == sf::Event::MouseButtonPressed &&
//		event.mouseButton.button == sf::Mouse::Button::Left)
//	{
//		if (hovered != NULL)
//		{
//			selected = hovered;
//		}
//		if (dtn::PixelToTile(mousePos) == sf::Vector2i(17, 0))
//		{
//			p1.draw();
//		}
//		else if (dtn::PixelToTile(mousePos) == sf::Vector2i(17, 17))
//		{
//			p2.draw();
//		}
//	}
//	else if (event.type == sf::Event::MouseButtonReleased &&
//		event.mouseButton.button == sf::Mouse::Button::Left)
//	{
//		if (selected != NULL && hovered != NULL &&
//			selected->getOwner() != hovered->getOwner())
//		{
//			selected->attack(hovered);
//		}
//		else if (selected != NULL)
//		{
//			sf::Vector2i tilePos = dtn::PixelToTile(mousePos);
//			sf::Vector2i runePos = dtn::PixelToTile(sf::Vector2i(
//				static_cast<int>(selected->getPos().x),
//				static_cast<int>(selected->getPos().y)));
//			int distance = dtn::TileDistance(tilePos, runePos);
//			if (selected->getState() == dtn::Runestone::state::IN_HAND &&
//				tilePos.x <= battlefield.getDimension().x &&
//				tilePos.x >= 1 &&
//				tilePos.y <= battlefield.getDimension().y &&
//				tilePos.y >= 1)
//			{
//				if (selected->getOwner() == 1 && battlefield.canPlayRunestone(selected, mousePos))
//				{
//					std::shared_ptr<dtn::Process> p(new dtn::ProcessMove(selected, sf::Vector2f(
//						static_cast<float>(tilePos.x)*dtn::PIXELS_PER_TILE,
//						static_cast<float>(tilePos.y)*dtn::PIXELS_PER_TILE)));
//					processManager.attachProcess(p);
//					battlefield.playRunestone(p1.playRunestone(selected));
//				}
//				else if (selected->getOwner() == 2 && battlefield.canPlayRunestone(selected, mousePos))
//				{
//					std::shared_ptr<dtn::Process> p(new dtn::ProcessMove(selected, sf::Vector2f(
//						static_cast<float>(tilePos.x)*dtn::PIXELS_PER_TILE,
//						static_cast<float>(tilePos.y)*dtn::PIXELS_PER_TILE)));
//					processManager.attachProcess(p);
//					battlefield.playRunestone(p2.playRunestone(selected));
//				}
//			}
//			else if (selected->getState() == dtn::Runestone::state::ON_BATTLEFIELD &&
//				tilePos.x <= battlefield.getDimension().x &&
//				tilePos.x >= 1 &&
//				tilePos.y <= battlefield.getDimension().y &&
//				tilePos.y >= 1 &&
//				distance <= selected->getSpeed())
//			{
//				std::shared_ptr<dtn::Process> p(new dtn::ProcessMove(selected, sf::Vector2f(
//					static_cast<float>(tilePos.x)*dtn::PIXELS_PER_TILE,
//					static_cast<float>(tilePos.y)*dtn::PIXELS_PER_TILE)));
//				processManager.attachProcess(p);
//			}
//		}
//		selected = NULL;
//	}
//	else if (event.type == sf::Event::MouseButtonPressed &&
//		event.mouseButton.button == sf::Mouse::Button::Right)
//	{
//		selected = NULL;
//	}
//	else if (event.type == sf::Event::KeyPressed &&
//		event.key.code == sf::Keyboard::Space)
//	{
//		currentPlayer = (currentPlayer == 1) ? 2 : 1;
//		hovered = NULL;
//		selected = NULL;
//	}
//}
//
//void Draw()
//{
//	window.clear(sf::Color::Black);
//	window.draw(backgroundSprite);
//	p1.render(window);
//	p2.render(window);
//	battlefield.render(window, currentPlayer);
//	tooltip.render(window);
//	window.display();
//
//	/*window2.clear(sf::Color::Black);
//	window2.draw(backgroundSprite);
//	p1.render(window2);
//	p2.render(window2);
//	battlefield.render(window2, 2);
//	tooltip.render(window2);
//	window2.display();*/
//}
//
//int main()
//{
//	Setup();
//
//	while (window.isOpen())
//	{
//		sf::Time dt = globalClock.restart();
//		processManager.update(dt.asSeconds());
//		battlefield.update();
//		mousePos = sf::Mouse::getPosition(window);
//		UpdateHovered();
//		
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			HandleEvent(event);
//		}
//		Draw();
//	}
//}