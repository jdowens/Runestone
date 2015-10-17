#include "gamescreen.h"

dtn::GameScreen::GameScreen(std::shared_ptr<sf::Texture> background, int playerID)
{
	m_backgroundTexture = background;
	m_background.setTexture(*m_backgroundTexture);
	m_tooltip.setInvisible();

	// attach listeners
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_DRAWN,
		std::bind(&GameScreen::onEntityDrawn, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_MOVED,
		std::bind(&GameScreen::onEntityMoved, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_BATTLE,
		std::bind(&GameScreen::onEntityBattle, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_ADDED,
		std::bind(&GameScreen::onEntityAdded, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_MOVE_FLAG_CHANGED,
		std::bind(&GameScreen::onEntityMoveFlagChanged, this, std::placeholders::_1));

	/*dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ADD_RENDERABLE,
		std::bind(&GameScreen::onAddRenderable, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::MOVE_RENDERABLE,
		std::bind(&GameScreen::onMoveRenderable, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::DELETE_RENDERABLE,
		std::bind(&GameScreen::onDeleteRenderable, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::UPDATE_RENDERABLE_LOS,
		std::bind(&GameScreen::onUpdateRenderableLos, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::UPDATE_RENDERABLE_TOOLTIP,
		std::bind(&GameScreen::onUpdateRenderableTooltip, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::UPDATE_RENDERABLE_OWNER,
		std::bind(&GameScreen::onUpdateRenderableOwner, this, std::placeholders::_1));*/

	m_playerID = playerID;
}

dtn::GameScreen::GameScreen(int playerID)
{
	m_tooltip.setInvisible();

	// attach listeners
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_DRAWN,
		std::bind(&GameScreen::onEntityDrawn, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_MOVED,
		std::bind(&GameScreen::onEntityMoved, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_BATTLE,
		std::bind(&GameScreen::onEntityBattle, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_ADDED,
		std::bind(&GameScreen::onEntityAdded, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ENTITY_MOVE_FLAG_CHANGED,
		std::bind(&GameScreen::onEntityMoveFlagChanged, this, std::placeholders::_1));

	/*dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::ADD_RENDERABLE,
		std::bind(&GameScreen::onAddRenderable, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::MOVE_RENDERABLE,
		std::bind(&GameScreen::onMoveRenderable, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::DELETE_RENDERABLE,
		std::bind(&GameScreen::onDeleteRenderable, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::UPDATE_RENDERABLE_LOS,
		std::bind(&GameScreen::onUpdateRenderableLos, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::UPDATE_RENDERABLE_TOOLTIP,
		std::bind(&GameScreen::onUpdateRenderableTooltip, this, std::placeholders::_1));
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::UPDATE_RENDERABLE_OWNER,
		std::bind(&GameScreen::onUpdateRenderableOwner, this, std::placeholders::_1));*/
	m_playerID = playerID;
}

void dtn::GameScreen::loadBackground(std::string fileName)
{
	m_backgroundTexture = std::shared_ptr<sf::Texture>(new sf::Texture);
	m_backgroundTexture->loadFromFile(fileName);
	m_background.setTexture(*m_backgroundTexture);
}

void dtn::GameScreen::moveBackground(sf::Vector2f newLoc)
{
	m_background.setPosition(newLoc); 
}

void dtn::GameScreen::update(float dt)
{
	std::vector<std::shared_ptr<dtn::Event>> ret;
	m_processManager.update(dt);
}

void dtn::GameScreen::render(sf::RenderWindow& window, int playerID)
{
	window.draw(m_background);
	for (std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it = m_renderables.begin();
		it != m_renderables.end(); ++it)
	{
		if (it->second->getHasMoved())
		{
			it->second->getSprite().setColor(sf::Color::Yellow);
		}
		else
		{
			// color the sprites based on the owner
			if (it->second->getOwner() == m_playerID)
			{
				it->second->getSprite().setColor(sf::Color::Blue);
			}
			else
			{
				it->second->getSprite().setColor(sf::Color::Red);
			}
		}
		window.draw(it->second->getSprite());
	}
	m_tooltip.render(window);
}

void dtn::GameScreen::pushRenderable(int entityID, std::shared_ptr<dtn::Renderable> renderable)
{
	m_renderables.insert(std::pair<int, std::shared_ptr<dtn::Renderable>>(entityID, renderable));
}

void dtn::GameScreen::removeRenderable(int entityID)
{
	std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it =
		m_renderables.find(entityID);
	if (it != m_renderables.end())
		m_renderables.erase(it);
}

std::shared_ptr<dtn::Renderable> dtn::GameScreen::getRenderableAt(sf::Vector2i position)
{
	for (std::map<int, std::shared_ptr<dtn::Renderable>>::reverse_iterator it
		= m_renderables.rbegin(); it != m_renderables.rend(); ++it)
	{
		if (it->second->getSprite().getGlobalBounds().contains(dtn::Utilities::IntVecToFloat(position)))
		{
			return it->second;
		}
	}
	return std::shared_ptr<dtn::Renderable>();
}

std::shared_ptr<dtn::Renderable> dtn::GameScreen::getRenderableAt(sf::Vector2f position)
{
	for (std::map<int, std::shared_ptr<dtn::Renderable>>::reverse_iterator it
		= m_renderables.rbegin(); it != m_renderables.rend(); ++it)
	{
		if (it->second->getSprite().getGlobalBounds().contains(position))
		{
			return it->second;
		}
	}
	return std::shared_ptr<dtn::Renderable>();
}

void dtn::GameScreen::onAddRenderable(std::shared_ptr<dtn::Event> e)
{
	EventAddRenderable* cast = dynamic_cast<EventAddRenderable*>(e.get());
	std::shared_ptr<dtn::Renderable> rend = dtn::RenderableFactory::getInstance()->newRenderable(
		cast->renderableID, cast->entityID);
	rend->getSprite().setPosition(dtn::Utilities::TileToFloat(cast->pos));
	pushRenderable(cast->entityID, rend);
}

void dtn::GameScreen::onMoveRenderable(std::shared_ptr<dtn::Event> e)
{
	EventMoveRenderable* cast = dynamic_cast<EventMoveRenderable*>(e.get());
	std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it
		= m_renderables.find(cast->entityID);
	bool valid = true;
	if (it == m_renderables.end())
	{
		std::cout << "INVALID MOVE_RENDERABLE EVENT PASSED TO GAME_SCREEN, ENTITY ID: "
			<< cast->entityID << '\n';
		valid = false;
	}
	if (valid)
	{
		std::shared_ptr<dtn::Process> process =
			std::shared_ptr<dtn::ProcessMoveRenderable>(new ProcessMoveRenderable(
			it->second, dtn::Utilities::TileToFloat(cast->dest), cast->velocity));
		m_processManager.attachProcess(process);
	}
}

void dtn::GameScreen::onDeleteRenderable(std::shared_ptr<dtn::Event> e)
{
	EventDeleteRenderable* cast = dynamic_cast<EventDeleteRenderable*>(e.get());
	removeRenderable(cast->entityID);
}

void dtn::GameScreen::onUpdateRenderableLos(std::shared_ptr<dtn::Event> e)
{
	EventUpdateRenderableLos* cast = dynamic_cast<EventUpdateRenderableLos*>(e.get());
	std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it
		= m_renderables.find(cast->entityID);
	bool valid = true;
	if (it == m_renderables.end())
	{
		std::cout << "INVALID UPDATE_RENDERABLE_LOS EVENT PASSED TO GAME_SCREEN, ENTITY ID: "
			<< cast->entityID << '\n';
		valid = false;
	}
	if (valid)
	{
		it->second->setLos(cast->los);
	}
}

void dtn::GameScreen::onUpdateRenderableTooltip(std::shared_ptr<dtn::Event> e)
{
	EventUpdateRenderableTooltip* cast = dynamic_cast<EventUpdateRenderableTooltip*>(e.get());
	std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it
		= m_renderables.find(cast->entityID);
	bool valid = true;
	if (it == m_renderables.end())
	{
		std::cout << "INVALID UPDATE_RENDERABLE_TOOLTIP EVENT PASSED TO GAME_SCREEN, ENTITY ID: "
			<< cast->entityID << '\n';
		valid = false;
	}
	if (valid)
	{
		it->second->setToolTip(cast->tooltip);
	}
}

void dtn::GameScreen::onUpdateRenderableOwner(std::shared_ptr<dtn::Event> e)
{
	EventUpdateRenderableOwner* cast = dynamic_cast<EventUpdateRenderableOwner*>(e.get());
	std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it
		= m_renderables.find(cast->entityID);
	bool valid = true;
	if (it == m_renderables.end())
	{
		std::cout << "INVALID UPDATE_RENDERABLE_OWNER EVENT PASSED TO GAME_SCREEN, ENTITY ID: "
			<< cast->entityID << '\n';
		valid = false;
	}
	if (valid)
	{
		it->second->setOwner(cast->owner);
	}
}

void dtn::GameScreen::onEntityDrawn(std::shared_ptr<dtn::Event> e)
{
	dtn::EventEntityDrawn* cast = dynamic_cast<EventEntityDrawn*>(e.get());

	// add renderable
	std::shared_ptr<dtn::Renderable> rend = dtn::RenderableFactory::getInstance()->newRenderable(
		cast->renderableID, cast->entityID);
	rend->getSprite().setPosition(dtn::Utilities::TileToFloat(
		dtn::Utilities::LocalTileToGlobal(cast->source, m_playerID)));
	pushRenderable(cast->entityID, rend);

	// update renderable stats and queue movement
	std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it
		= m_renderables.find(cast->entityID);
	bool valid = true;
	if (it == m_renderables.end())
	{
		std::cout << "INVALID ENTITY_DRAWN EVENT PASSED TO GAME_SCREEN, ENTITY ID: "
			<< cast->entityID << '\n';
		valid = false;
	}
	if (valid)
	{
		it->second->setLos(cast->los);
		it->second->setOwner(cast->owner);
		it->second->setToolTip(cast->tooltip);
		std::shared_ptr<dtn::Process> process =
			std::shared_ptr<dtn::ProcessMoveRenderable>(new ProcessMoveRenderable(
			it->second, dtn::Utilities::TileToFloat(dtn::Utilities::LocalTileToGlobal(
			cast->dest, m_playerID)), 600.f));
		m_processManager.attachProcess(process);
	}
}

void dtn::GameScreen::onEntityMoved(std::shared_ptr<dtn::Event> e)
{
	dtn::EventEntityMoved* cast = dynamic_cast<EventEntityMoved*>(e.get());

	// find entity, queue movement process and update tooltip
	std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it
		= m_renderables.find(cast->entityID);
	bool valid = true;
	if (it == m_renderables.end())
	{
		std::cout << "INVALID MOVE_RENDERABLE EVENT PASSED TO GAME_SCREEN, ENTITY ID: "
			<< cast->entityID << '\n';
		valid = false;
	}
	if (valid)
	{
		std::shared_ptr<dtn::Process> process =
			std::shared_ptr<dtn::ProcessMoveRenderable>(new ProcessMoveRenderable(
			it->second, dtn::Utilities::TileToFloat(dtn::Utilities::LocalTileToGlobal(
			cast->dest, m_playerID)), 600.f));
		m_processManager.attachProcess(process);
		it->second->setToolTip(cast->tooltip);
	}
}

void dtn::GameScreen::onEntityBattle(std::shared_ptr<dtn::Event> e)
{
	EventEntityBattle* cast = dynamic_cast<EventEntityBattle*>(e.get());

	// find entities and update tooltips
	std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it1
		= m_renderables.find(cast->attackerEntityID);
	std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it2
		= m_renderables.find(cast->defenderEntityID);
	bool valid = true;
	if (it1 == m_renderables.end() || it2 == m_renderables.end())
	{
		std::cout << "INVALID ENTITY_BATTLE EVENT PASSED TO GAME_SCREEN, ENTITY ID: "
			<< cast->attackerEntityID << '\n';
		valid = false;
	}
	if (valid)
	{
		it1->second->setToolTip(cast->tooltipAttacker);
		it2->second->setToolTip(cast->tooltipDefender);
		if (cast->attackerDead)
			removeRenderable(cast->attackerEntityID);
		else
			m_processManager.attachProcess(std::shared_ptr<dtn::Process>(
				new ProcessShakeRenderable(it1->second, sf::Vector2f(10.0f, 10.0f), 0.35f)));
		if (cast->defenderDead)
			removeRenderable(cast->defenderEntityID);
		else
			m_processManager.attachProcess(std::shared_ptr<dtn::Process>(
				new ProcessShakeRenderable(it2->second, sf::Vector2f(10.0f, 10.0f), 0.35f)));
	}
}

void dtn::GameScreen::onEntityAdded(std::shared_ptr<dtn::Event> e)
{
	EventEntityAdded* cast = dynamic_cast<EventEntityAdded*>(e.get());

	// add renderable
	std::shared_ptr<dtn::Renderable> rend = dtn::RenderableFactory::getInstance()->newRenderable(
		cast->renderableID, cast->entityID);
	rend->getSprite().setPosition(dtn::Utilities::TileToFloat(
		dtn::Utilities::LocalBoundsToGlobalPosition(cast->bounds, m_playerID)));
	pushRenderable(cast->entityID, rend);

	// update renderable stats
	std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it
		= m_renderables.find(cast->entityID);
	bool valid = true;
	if (it == m_renderables.end())
	{
		std::cout << "INVALID ENTITY_DRAWN EVENT PASSED TO GAME_SCREEN, ENTITY ID: "
			<< cast->entityID << '\n';
		valid = false;
	}
	if (valid)
	{
		it->second->setLos(cast->los);
		it->second->setOwner(cast->owner);
		it->second->setToolTip(cast->tooltip);
	}
}

void dtn::GameScreen::onEntityMoveFlagChanged(std::shared_ptr<dtn::Event> e)
{
	EventEntityMoveFlagChanged* cast = dynamic_cast<EventEntityMoveFlagChanged*>(e.get());
	//std::cout << "IN ENTITY MOVE FLAG CHANGED!::::" << cast->entityID << '\n';
	for (std::map<int, std::shared_ptr<dtn::Renderable>>::iterator it = m_renderables.begin();
	it != m_renderables.end(); ++it)
	{
		if (it->second->getEntityID() == cast->entityID)
		{
			it->second->setHasMoved(cast->flag);
		}
	}
}
