#include "inputhandler.h"

dtn::InputHandler::InputHandler(int playerID)
{
	m_playerID = playerID;
	m_battlefieldZone = sf::IntRect(
		dtn::Utilities::BOARD_LEFT, dtn::Utilities::BOARD_TOP, 
		dtn::Utilities::BOARD_WIDTH, dtn::Utilities::BOARD_HEIGHT);
	if (m_playerID == 1)
	{
		m_summoningZone = 
			sf::IntRect(dtn::Utilities::BOARD_LEFT, dtn::Utilities::BOARD_HEIGHT + 
			dtn::Utilities::BOARD_TOP - 1,
			dtn::Utilities::BOARD_WIDTH, 1);
		m_handZone =
			sf::IntRect(dtn::Utilities::BOARD_LEFT, dtn::Utilities::BOARD_HEIGHT + 
			dtn::Utilities::BOARD_TOP,
			dtn::Utilities::BOARD_WIDTH, 1);
	}
	else if (m_playerID == 2)
	{
		m_summoningZone =
			sf::IntRect(dtn::Utilities::BOARD_LEFT, dtn::Utilities::BOARD_TOP, 
			dtn::Utilities::BOARD_WIDTH, 1);
		m_handZone =
			sf::IntRect(dtn::Utilities::BOARD_LEFT, dtn::Utilities::BOARD_TOP - 1, 
			dtn::Utilities::BOARD_WIDTH, 1);
	}
}

void dtn::InputHandler::update(sf::RenderWindow& window, dtn::GameScreen& screen, dtn::HUD& HUD)
{
	m_mousePos = sf::Mouse::getPosition(window);
	updateHovered(screen);
	handleEvents(window, HUD);
}

void dtn::InputHandler::updateHovered(dtn::GameScreen& screen)
{
	// cache last hovered piece to check if hovered piece has changed since last movement
	auto cache = m_hovered;
	m_hovered = NULL;
	m_hovered = screen.getRenderableAt(m_mousePos);

	// request movement decal if necessary
	if (m_hovered != cache && m_hovered != NULL)
	{
		if (!m_hovered->getHasMoved())
		{
			dtn::GlobalEventQueue::getInstance()->pushEvent(std::shared_ptr<Event>(
				new EventRequestEntityMoveDecal(m_playerID,
					dtn::Utilities::MouseToGlobalTile(dtn::Utilities::FloatVecToInt(
						m_hovered->getSprite().getPosition()), m_playerID))));
		}
	}

	if (m_hovered != NULL)
	{
		screen.m_tooltip.update(m_mousePos, m_hovered->getToolTip());
		screen.m_tooltip.setVisible();
	}
	else
	{
		screen.m_tooltip.setInvisible();
		screen.m_movementDecal.setInvisible();
	}
}

void dtn::InputHandler::handleEvents(sf::RenderWindow& window, dtn::HUD& hud)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// handle events for HUD first
		hud.handleEvent(event);
		if (event.type == sf::Event::Closed)
		{
			window.close();
			dtn::GlobalEventQueue::getInstance()->pushEvent(std::shared_ptr<dtn::Event>(new dtn::EventGameQuit()));
		}
		else if (event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Button::Left)
		{
			if (m_hovered != NULL)
			{
				m_selected = m_hovered;
			}
			if (dtn::Utilities::PixelToTile(m_mousePos) == sf::Vector2i(
				dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT, 
				(dtn::Utilities::BOARD_HEIGHT + dtn::Utilities::BOARD_TOP) / 2))
			{
				dtn::GlobalEventQueue::getInstance()->pushEvent(
					std::shared_ptr<dtn::Event>(new dtn::EventEndTurn(m_playerID)));
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased &&
			event.mouseButton.button == sf::Mouse::Button::Left)
		{
			if (m_selected != NULL && m_hovered != NULL)
			{
				sf::Vector2i tileSource = dtn::Utilities::MouseToGlobalTile(dtn::Utilities::FloatVecToInt(
					m_selected->getSprite().getPosition()), m_playerID);
				sf::Vector2i tileDest = dtn::Utilities::MouseToGlobalTile(dtn::Utilities::FloatVecToInt(
					m_hovered->getSprite().getPosition()), m_playerID);
				dtn::GlobalEventQueue::getInstance()->pushEvent(std::shared_ptr<dtn::Event>(
						new dtn::EventRunestoneAttack(tileSource, tileDest)));
			}
			else if (m_selected != NULL)
			{
				sf::Vector2i destPos = dtn::Utilities::MouseToGlobalTile(m_mousePos, m_playerID);
				sf::Vector2i sourcePos = dtn::Utilities::MouseToGlobalTile(dtn::Utilities::FloatVecToInt(
					m_selected->getSprite().getPosition()), m_playerID);
				if (m_handZone.contains(sourcePos))
				{
					dtn::GlobalEventQueue::getInstance()->pushEvent(std::shared_ptr<dtn::Event>(
						new dtn::EventRunestonePlay(m_selected->getEntityID(), destPos)));
				}
				else if (m_battlefieldZone.contains(sourcePos))
				{
					dtn::GlobalEventQueue::getInstance()->pushEvent(std::shared_ptr<dtn::Event>(
						new dtn::EventRunestoneMove(sourcePos, destPos)));
				}
			}
			m_selected = NULL;
		}
		else if (event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Button::Right)
		{
			m_selected = NULL;
		}
		else if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Space)
		{
			dtn::GlobalEventQueue::getInstance()->pushEvent(std::shared_ptr<dtn::Event>(
				new dtn::EventEndTurn(m_playerID)));
		}
		else if (event.type == sf::Event::Resized)
		{
			//dtn::Utilities::OnResized(event.size.width, event.size.height);
		}
	}
}

