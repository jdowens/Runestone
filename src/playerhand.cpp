#include "playerhand.h"

// constructor
dtn::PlayerHand::PlayerHand(int playerID)
{
	m_playerID = playerID;
}

// addRunestone
/*
	Add and take ownership of a runestone.
*/
void dtn::PlayerHand::addRunestone(std::shared_ptr<dtn::Runestone> runestone)
{
	runestone->setOwner(m_playerID);
	runestone->setState(dtn::Runestone::state::IN_HAND);
	m_runestones.push_back(runestone);
}

// containsRunestone
/*
	Check by entityID if a runestone is in the hand.
*/
bool dtn::PlayerHand::containsRunestone(int entityID)
{
	for (std::vector<std::shared_ptr<dtn::Runestone>>::iterator it = m_runestones.begin();
		it != m_runestones.end(); ++it)
	{
		if (entityID == (*it)->getEntityID())
		{
			return true;
		}
	}
	return false;
}

// getRunestoneAt
/*
	Get the runestone specified by the input tile position.
*/
std::shared_ptr<dtn::Runestone> dtn::PlayerHand::getRunestoneAt(sf::Vector2i position)
{
	int count = dtn::Utilities::BOARD_LEFT;
	for (std::vector<std::shared_ptr<dtn::Runestone>>::iterator it = m_runestones.begin();
		it != m_runestones.end(); ++it)
	{
		if (position.x == count++)
		{
			return *it;
		}
	}
	return std::shared_ptr<dtn::Runestone>();
}

// getRunestoneByEntityID
/*
	Grab a runestone corresponding to a given entityID.
*/
std::shared_ptr<dtn::Runestone> dtn::PlayerHand::getRunestoneByEntityID(int entityID)
{
	for (std::vector<std::shared_ptr<dtn::Runestone>>::iterator it = m_runestones.begin();
		it != m_runestones.end(); ++it)
	{
		if (entityID == (*it)->getEntityID())
		{
			return *it;
		}
	}
	return std::shared_ptr<dtn::Runestone>();
}

// getLastDrawn
/*
	Return the last drawn runestone.
*/
std::shared_ptr<dtn::Runestone> dtn::PlayerHand::getLastDrawn()
{
	return m_runestones.back();
}

// playRunestone
/*
	Relinquish control of a runestone.
*/
std::shared_ptr<dtn::Runestone> dtn::PlayerHand::playRunestone(std::shared_ptr<dtn::Runestone> runestone)
{
	std::shared_ptr<dtn::Runestone> ret = NULL;
	for (std::vector<std::shared_ptr<dtn::Runestone>>::iterator it = m_runestones.begin();
		it != m_runestones.end(); ++it)
	{
		if ((*it) == runestone)
		{
			ret = *it;
			ret->setState(dtn::Runestone::state::ON_BATTLEFIELD);
			ret->setHasMoved(true);
			ret->setHasAttacked(true);
			m_runestones.erase(it);
			break;
		}
	}
	return ret;
}

// getCount
int dtn::PlayerHand::getCount()
{
	return m_runestones.size();
}

// getNextCardPosition
sf::Vector2i dtn::PlayerHand::getNextCardPosition()
{
	sf::Vector2i ret;
	ret.x = dtn::Utilities::BOARD_LEFT + m_runestones.size();
	if (m_playerID == 1)
	{
		ret.y = dtn::Utilities::BOARD_TOP + dtn::Utilities::BOARD_HEIGHT;
	}
	else if (m_playerID == 2)
	{
		ret.y = dtn::Utilities::BOARD_TOP - 1;
	}
	return ret;
}

// getCardPosition
sf::Vector2i dtn::PlayerHand::getCardPosition(int index)
{
	sf::Vector2i ret;
	ret.x = dtn::Utilities::BOARD_LEFT + index;
	if (m_playerID == 1)
	{
		ret.y = dtn::Utilities::BOARD_TOP + dtn::Utilities::BOARD_HEIGHT;
	}
	else if (m_playerID == 2)
	{
		ret.y = dtn::Utilities::BOARD_TOP - 1;
	}
	return ret;
}

// getHand
const std::vector<std::shared_ptr<dtn::Runestone>>& dtn::PlayerHand::getHand()
{
	return m_runestones;
}

// render
void dtn::PlayerHand::render(sf::RenderWindow& window)
{
	sf::CircleShape circle(static_cast<float>(dtn::Utilities::PIXELS_PER_TILE_X) / 2.f);
	circle.setFillColor(sf::Color::White);
	int count = dtn::Utilities::BOARD_LEFT;
	for (std::vector<std::shared_ptr<dtn::Runestone>>::iterator it = m_runestones.begin();
		it != m_runestones.end(); ++it)
	{
		circle.setPosition(static_cast<float>(dtn::Utilities::PIXELS_PER_TILE_X*count++),
			dtn::Utilities::PIXELS_PER_TILE_Y*(dtn::Utilities::BOARD_HEIGHT + dtn::Utilities::BOARD_TOP));
		window.draw(circle);
	}
}