#include "gameclientai.h"

dtn::GameClientAI::GameClientAI(int playerID, std::string ip, 
	std::shared_ptr<EventManager> eventManager,
	std::shared_ptr<GameServer> serverRef)
	: GameClient(playerID, ip, eventManager)
{
	m_serverRef = serverRef;
	m_currentTime = 0;
	m_currentStep = 0;
	m_timeBetweenActions = 0.25;
}

void dtn::GameClientAI::update(float dt)
{
	// if the AI's turn
	if (m_serverRef->m_currentPlayer == m_playerID)
	{
		m_currentTime += dt;
		if (m_currentTime > m_timeBetweenActions)
		{
			m_currentTime = 0;
			step();
			if (m_currentStep == 3)
			{
				m_eventManager->pushEvent(
					std::make_shared<EventEndTurn>(m_playerID));
				m_currentStep = 0;
			}
		}
		m_eventManager->update();
	}
}

void dtn::GameClientAI::step()
{
	switch (m_currentStep)
	{
	case 0 :
		playOutHand(); break;
	case 1 :
		moveAllPieces(); break;
	case 2 :
		attackInRange(); break;
	}
}

void dtn::GameClientAI::playOutHand()
{
	auto player = &m_serverRef->m_players[m_serverRef->m_currentPlayer - 1];
	auto hand = player->getHand();
	std::sort(hand.rbegin(), hand.rend(), dtn::SortRunestoneByCost);
	auto battlefield = &m_serverRef->m_battlefield;
	bool playedSomething = false;
	for (auto it = hand.begin(); it != hand.end(); ++it)
	{
		if ((*it)->getCost() <= player->getCurrentMana())
		{
			for (int i = dtn::Utilities::BOARD_LEFT; i < dtn::Utilities::BOARD_LEFT +
				dtn::Utilities::BOARD_WIDTH; i++)
			{
				sf::Vector2i pos = 
					dtn::Utilities::LocalTileToGlobal(
						sf::Vector2i(i, dtn::Utilities::BOARD_TOP + dtn::Utilities::BOARD_HEIGHT - 1), m_playerID);
				if (battlefield->getEntityBattlefieldAt(pos) == NULL)
				{
					m_eventManager->pushEvent(std::make_shared<EventRunestonePlay>(
						(*it)->getEntityID(), pos));
					playedSomething = true;
					// found somewhere to play
					break;
				}
			}
		}
	}
	if (playedSomething == false)
		m_currentStep++;
}

void dtn::GameClientAI::moveAllPieces()
{
	auto battlefield = &m_serverRef->m_battlefield;
	auto rune = m_serverRef->m_battlefield.getFirstMoveableEntity(m_playerID);
	if (rune == NULL)
		m_currentStep++;
	else
	{
		auto dest = battlefield->pathToEnemyBase(rune);
		m_eventManager->pushEvent(std::make_shared<EventRunestoneMove>(
			rune->getTilePos(), dest));
	}
}

void dtn::GameClientAI::attackInRange()
{
	auto battlefield = &m_serverRef->m_battlefield;
	auto runes = m_serverRef->m_battlefield.getAllOwnedRunes(m_playerID);
	for (auto it = runes.begin(); it != runes.end(); ++it)
	{
		auto closest = battlefield->closestEnemyInRange(*it);
		if (closest != NULL)
		{
			m_eventManager->pushEvent(std::make_shared<EventRunestoneAttack>(
				(*it)->getTilePos(), closest->getTilePos()));
		}
	}
	m_currentStep++;
}
