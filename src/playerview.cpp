#include "playerview.h"

dtn::PlayerView::PlayerView(int playerID) : View(playerID), m_window(
	sf::VideoMode(dtn::Utilities::WINDOW_WIDTH, dtn::Utilities::WINDOW_HEIGHT, 32), "Player View Test"), m_player(playerID),
	m_battlefield(sf::Vector2i(dtn::Utilities::BOARD_WIDTH, dtn::Utilities::BOARD_HEIGHT)),
	m_screen(playerID)
{
	m_window.setVisible(false);
	m_screen.loadBackground("Resources/tilemap.png");
	m_screen.moveBackground(sf::Vector2f(static_cast<float>(dtn::Utilities::PIXELS_PER_TILE_X*
		dtn::Utilities::BOARD_LEFT), static_cast<float>(
		dtn::Utilities::PIXELS_PER_TILE_Y*dtn::Utilities::BOARD_TOP)));
	m_clock.restart();
	m_player.draft();
	m_player2Cards = 3;
	m_player2DeckAmount = 27;
	m_tooltipActive = false;
	m_isTurn = (m_playerID == 1) ? true : false;
	draw(); draw(); draw();
	m_window.setVisible(true);
}



std::vector<std::shared_ptr<dtn::Event>> dtn::PlayerView::Update(
	std::vector<std::shared_ptr<dtn::Event>> events)
{
	m_returnEvents.clear();
	handleEventList(events);
	sf::Time dt = m_clock.restart();
	m_battlefield.update();
	m_mousePos = sf::Mouse::getPosition(m_window);
	updateHovered();

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		handleEvent(event);
	}
	render();

	return m_returnEvents;
}

void dtn::PlayerView::updateHovered()
{
	std::stringstream ss;
	if (m_mousePos.y > dtn::Utilities::PIXELS_PER_TILE_Y * (
		dtn::Utilities::BOARD_HEIGHT + dtn::Utilities::BOARD_TOP) &&
		m_mousePos.x < dtn::Utilities::PIXELS_PER_TILE_X * (
		dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT))
	{
		m_hovered = m_player.getRunestoneAt(dtn::Utilities::MouseToGlobalTile(m_mousePos, m_playerID));
	}
	else if (dtn::Utilities::PixelToTile(m_mousePos) == sf::Vector2i(
		dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT,
		dtn::Utilities::BOARD_TOP + dtn::Utilities::BOARD_HEIGHT))
	{
		m_tooltipActive = true;
		ss << m_player.toString();
		m_hovered = NULL;
	}
	else if (dtn::Utilities::PixelToTile(m_mousePos) == sf::Vector2i(
		(dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT),
		(dtn::Utilities::BOARD_TOP - 1)))
	{
		m_tooltipActive = true;
		ss << "Cards in deck: " << m_player2DeckAmount << '\n';
		m_hovered = NULL;
	}
	else
	{
		if (m_battlefield.isVisible(dtn::Utilities::MouseToGlobalTile(m_mousePos, m_playerID), m_playerID))
		{
			m_hovered = m_battlefield.getEntityBattlefieldAt(dtn::Utilities::MouseToGlobalTile(m_mousePos, m_playerID));
		}
		else
		{
			m_hovered = NULL;
		}
	}
	if (m_hovered != NULL)
	{
		m_tooltip.setVisible();
		m_tooltip.setText(m_hovered->toString());
		m_tooltip.setLocation(m_mousePos);
	}
	else if (m_tooltipActive)
	{
		
		m_tooltip.setVisible();
		m_tooltip.setText(ss.str());
		m_tooltip.setLocation(m_mousePos);
	}
	else
	{
		m_tooltip.setInvisible();
	}
	m_tooltipActive = false;
}

void dtn::PlayerView::handleEventList(std::vector<std::shared_ptr<dtn::Event>> events)
{
	for (std::vector<std::shared_ptr<dtn::Event>>::iterator it = events.begin();
		it != events.end(); ++it)
	{
		std::shared_ptr<Event> cur = (*it);
		if (cur == NULL)
			break;
		EventEndTurn* cast0 = NULL;
		EventRunestoneMove* cast1 = NULL;
		EventRunestonePlay* cast2 = NULL;
		EventRunestoneAttack* cast3 = NULL;
		switch (cur->getType())
		{
		case dtn::Event::EventType::END_TURN :
			m_isTurn = true; draw(); m_battlefield.resetEntityBattlefieldFlags();
			m_player.increaseMana(); m_player.resetCurrentMana(); break;
		case dtn::Event::EventType::RUNESTONE_DRAW: m_player2DeckAmount--; 
			m_player2Cards++; break;
		case dtn::Event::EventType::RUNESTONE_MOVE: 
			cast1 = dynamic_cast<EventRunestoneMove*>(cur.get());
			m_battlefield.moveEntityBattlefield(cast1->source, cast1->dest); break;
		case dtn::Event::EventType::RUNESTONE_PLAY:
			cast2 = dynamic_cast<EventRunestonePlay*>(cur.get());
			//m_battlefield.playEntityBattlefield(std::shared_ptr<Runestone>(new Runestone(cast2->runestone)), cast2->dest);
			m_player2Cards--;
			break;
		case dtn::Event::EventType::RUNESTONE_ATTACK:
			cast3 = dynamic_cast<EventRunestoneAttack*>(cur.get());
			m_battlefield.attackEntityBattlefield(cast3->source, cast3->dest); break;
		}
	}
}

void dtn::PlayerView::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed)
	{
		m_window.close();
		m_returnEvents.push_back(std::shared_ptr<dtn::Event>(new dtn::EventGameQuit()));
	}
	else if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left && m_isTurn)
	{
		if (m_hovered != NULL && m_hovered->getOwner() == m_playerID)
		{
			m_selected = m_hovered;
		}
		if (dtn::Utilities::PixelToTile(m_mousePos) == sf::Vector2i(
			dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT, 
			(dtn::Utilities::BOARD_HEIGHT + dtn::Utilities::BOARD_TOP) / 2))
		{
			m_isTurn = false;
			m_returnEvents.push_back(std::shared_ptr<dtn::Event>(new dtn::EventEndTurn(m_playerID)));
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Button::Left && m_isTurn)
	{
		if (m_selected != NULL && m_hovered != NULL &&
			m_selected->getOwner() != m_hovered->getOwner())
		{
			if (m_selected->canAttack(m_hovered))
			{
				m_selected->attack(m_hovered);
				m_returnEvents.push_back(std::shared_ptr<dtn::Event>(
					new dtn::EventRunestoneAttack(m_selected->getTilePos(), m_hovered->getTilePos())));
			}
		}
		else if (m_selected != NULL && m_selected->getType() == dtn::Entity::EntityType::RUNESTONE)
		{
			std::shared_ptr<dtn::Runestone> rune(std::dynamic_pointer_cast<dtn::Runestone>(m_selected));
			sf::Vector2i tilePos = dtn::Utilities::MouseToGlobalTile(m_mousePos, m_playerID);
			sf::Vector2i runePos = m_selected->getTilePos();
			if (rune->getState() == dtn::Runestone::state::IN_HAND)
			{
				if (m_player.playRunestone(rune, tilePos, m_battlefield))
				{
	//				m_returnEvents.push_back(std::shared_ptr<dtn::Event>(
	//					new dtn::EventRunestonePlay(*rune, tilePos)));
				}
			}
			else if (rune->getState() == dtn::Runestone::state::ON_BATTLEFIELD)
			{
				if (m_player.moveRunestone(rune, tilePos, m_battlefield))
				{
					m_returnEvents.push_back(std::shared_ptr<dtn::Event>(
						new dtn::EventRunestoneMove(runePos, tilePos)));
				}
			}
		}
		m_selected = NULL;
	}
	else if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Right)
	{
		m_selected = NULL;
	}
}

void dtn::PlayerView::render()
{
	m_window.clear();
	m_screen.render(m_window, m_playerID);
	m_player.render(m_window);
	renderOtherPlayerCards();
	m_battlefield.render(m_window, m_playerID);
	renderMisc();
	m_tooltip.render(m_window);
	m_window.display();
}

void dtn::PlayerView::renderOtherPlayerCards()
{
	sf::CircleShape circle(static_cast<float>(dtn::Utilities::PIXELS_PER_TILE_X) / 2.f);
	circle.setFillColor(sf::Color::White);
	for (int i = 0; i < m_player2Cards; i++)
	{
		circle.setPosition(static_cast<float>(dtn::Utilities::PIXELS_PER_TILE_X*
			(i + dtn::Utilities::BOARD_LEFT)),
			dtn::Utilities::PIXELS_PER_TILE_Y*(dtn::Utilities::BOARD_TOP - 1));
		m_window.draw(circle);
	}
	if (m_player2DeckAmount > 0)
	{
		circle.setPosition(dtn::Utilities::PIXELS_PER_TILE_X *
			(dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT), 
			dtn::Utilities::PIXELS_PER_TILE_Y*(dtn::Utilities::BOARD_TOP - 1));
		m_window.draw(circle);
	}
}

void dtn::PlayerView::renderMisc()
{
	sf::RectangleShape rect(sf::Vector2f(static_cast<float>(dtn::Utilities::PIXELS_PER_TILE_X),
		static_cast<float>(dtn::Utilities::PIXELS_PER_TILE_Y)));
	sf::Vector2i tilePos = sf::Vector2i(dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT,
		((dtn::Utilities::BOARD_HEIGHT + dtn::Utilities::BOARD_TOP) / 2));
	rect.setPosition(dtn::Utilities::TileToFloat(tilePos));
	rect.setFillColor(sf::Color::Red);
	m_window.draw(rect);
}

/////////////////////

void dtn::PlayerView::draw()
{
	if (m_player.draw())
	{
		m_returnEvents.push_back(std::shared_ptr<dtn::Event>(new dtn::EventRunestoneDraw(m_playerID)));
	}
}