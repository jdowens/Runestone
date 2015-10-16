//#include "gamescreen.h"
//#include "renderable.h"
//#include "processmoverenderable.h"
//#include "processmanager.h"
//#include<SFML/Graphics.hpp>
//#include<SFML/Window.hpp>
//
//#include<memory>
//#include<iostream>
//#include<vector>
//
//std::vector<std::shared_ptr<sf::Texture>> textures;
//
//std::shared_ptr<dtn::GameScreen> p1, p2;
//dtn::ProcessManager pManager;
//std::shared_ptr<dtn::Renderable> hovered = 0;
//std::shared_ptr<dtn::Renderable> selected = 0;
//sf::Vector2i mousePos(0, 0);
//
//sf::Clock globalClock;
//
//sf::RenderWindow window(sf::VideoMode(1024, 768, 32), "Game Screen Test...");
//
//int count = 1;
//
//bool p1Render = true;
//
//void UpdateHovered()
//{
//	if (p1Render)
//	{
//		hovered = p1->getRenderableAt(mousePos);
//	}
//	else
//	{
//		hovered = p2->getRenderableAt(mousePos);
//	}
//}
//
//void HandleEvent(sf::Event event)
//{
//	if (event.type == sf::Event::Closed)
//	{
//		window.close();
//	}
//	else if (event.type == sf::Event::KeyPressed &&
//		event.key.code == sf::Keyboard::Space)
//	{
//		p1Render = !p1Render;
//		hovered = NULL;
//		selected = NULL;
//	}
//	else if (event.type == sf::Event::MouseButtonPressed &&
//		event.mouseButton.button == sf::Mouse::Button::Left)
//	{
//		if (hovered != NULL)
//		{
//			selected = hovered;
//		}
//	}
//	else if (event.type == sf::Event::MouseButtonReleased &&
//		event.mouseButton.button == sf::Mouse::Button::Left)
//	{
//		if (selected != NULL)
//		{
//			sf::Vector2i tilePos = dtn::PixelToTile(mousePos);
//			sf::Vector2i selectedPos = 
//				dtn::PixelToTile(static_cast<sf::Vector2i>(selected->getSprite().getPosition()));
//				std::shared_ptr<dtn::Process> p(new dtn::ProcessMoveRenderable(selected, sf::Vector2f(
//				static_cast<float>(tilePos.x)*dtn::PIXELS_PER_TILE,
//				static_cast<float>(tilePos.y)*dtn::PIXELS_PER_TILE)));
//				pManager.attachProcess(p);
//		}
//	}
//}
//
//void Init()
//{
//	std::shared_ptr<sf::Texture> back(new sf::Texture());
//	back->loadFromFile("Resources/64grid.png");
//	std::shared_ptr<sf::Texture> icon1(new sf::Texture());
//	icon1->loadFromFile("Resources/small_icons/brutal-helm.png");
//	std::shared_ptr<sf::Texture> icon2(new sf::Texture());
//	icon2->loadFromFile("Resources/small_icons/flame.png");
//
//	textures.push_back(back);
//	textures.push_back(icon1);
//	textures.push_back(icon2);
//
//	p1 = std::shared_ptr<dtn::GameScreen>(new dtn::GameScreen(textures[0]));
//	p2 = std::shared_ptr<dtn::GameScreen>(new dtn::GameScreen(textures[0]));
//
//	std::shared_ptr<dtn::Renderable> r1(new dtn::Renderable(count++, textures[1]));
//	r1->getSprite().setPosition(sf::Vector2f(100.f, 100.f));
//	std::shared_ptr<dtn::Renderable> r2(new dtn::Renderable(count++, textures[2]));
//	r2->getSprite().setPosition(sf::Vector2f(500, 100.f));
//	std::shared_ptr<dtn::Renderable> r3(new dtn::Renderable(count++, textures[1]));
//	r3->getSprite().setPosition(sf::Vector2f(350, 0.f));
//	std::shared_ptr<dtn::Renderable> r4(new dtn::Renderable(count++, textures[2]));
//	r4->getSprite().setPosition(sf::Vector2f(0.f, 600.f));
//
//	p1->pushRenderable(r1);
//	p1->pushRenderable(r2);
//	p2->pushRenderable(r3);
//	p2->pushRenderable(r4);
//}
//
//
//int main()
//{
//	Init();
//	while (window.isOpen())
//	{
//		sf::Time dt = globalClock.restart();
//		pManager.update(dt.asSeconds());
//		mousePos = sf::Mouse::getPosition(window);
//		UpdateHovered();
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			HandleEvent(event);
//		}
//		window.clear();
//		if (p1Render)
//		{
//			p1->render(window);
//		}
//		else
//		{
//			p2->render(window);
//		}
//		window.display();
//	}
//}