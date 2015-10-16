//#include "gamescreen.h"
//#include "tooltip.h"
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Testing Game Screen...");
//	dtn::GameScreen screen;
//	dtn::Tooltip tooltip;
//	screen.loadBackground("Resources/grid.png");
//	sf::Clock clock;
//	std::vector<std::shared_ptr<dtn::Event>> events;
//	std::shared_ptr<dtn::Event> e1(new dtn::EventAddRenderable(sf::Vector2i(12, 3),
//		0, 0));
//	std::shared_ptr<dtn::Event> e2(new dtn::EventUpdateRenderableLos(0, 5));
//	std::shared_ptr<dtn::Event> e3(new dtn::EventUpdateRenderableTooltip(0, "What a lame tooltip...\n"));
//	std::shared_ptr<dtn::Event> e4(new dtn::EventUpdateRenderableOwner(0, 1));
//	events.push_back(e1);
//	events.push_back(e2);
//	events.push_back(e3);
//	events.push_back(e4);
//	while (window.isOpen())
//	{
//		sf::Event event;
//		float dt = clock.restart().asSeconds();
//		screen.update(dt, events);
//		events.clear();
//		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//		std::shared_ptr<dtn::Renderable> rend = screen.getRenderableAt(mousePos);
//		if (rend != NULL)
//		{
//			tooltip.setText(rend->getToolTip());
//			tooltip.setLocation(mousePos);
//			tooltip.setVisible();
//			std::cout << rend->getLos() << ' ' << rend->getOwner() << '\n';
//		}
//		else
//		{
//			tooltip.setInvisible();
//		}
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//			}
//			else if (event.type == sf::Event::MouseButtonPressed)
//			{
//				if (event.mouseButton.button == sf::Mouse::Button::Left)
//				{
//					std::shared_ptr<dtn::Event> e(new dtn::EventMoveRenderable(
//						0, sf::Vector2i(4, 8), 100));
//					events.push_back(e);
//				}
//				else
//				{
//					std::shared_ptr<dtn::Event> e(new dtn::EventDeleteRenderable(0));
//					events.push_back(e);
//				}
//			}
//		}
//		window.clear();
//		screen.render(window);
//		tooltip.render(window);
//		window.display();
//	}
//}