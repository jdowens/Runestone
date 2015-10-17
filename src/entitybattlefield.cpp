#include "entitybattlefield.h"
#include "globaleventqueue.h"

// initialize global EntityBattlefield counter
int dtn::EntityBattlefield::m_battlefieldEntityCount = 0;

// two parameter constructor
/*
	Call parent constructor and increase static counter
*/
dtn::EntityBattlefield::EntityBattlefield(int count, dtn::Entity::EntityType type)
	: Entity(count, type)
{
	m_hasMoved = false;
	m_battlefieldEntityCount++;
}

// constructor
/*
	Just increase count and call default parent constructor
*/
dtn::EntityBattlefield::EntityBattlefield()
{
	m_hasMoved = false;
	m_battlefieldEntityCount++;
}

// attack
/*
	Updates the stat outcome of a battle between two entities.
*/
void dtn::EntityBattlefield::attack(std::shared_ptr<dtn::EntityBattlefield> target)
{
	// if in range of target
	if (dtn::Utilities::TileDistance(getBounds(), target->getBounds()) <= target->getRange())
	{
		// receive damage
		m_currentHealth -= target->m_damage;
	}
	// deal damage to target (range here is checked by battlefield)
	target->m_currentHealth -= m_damage;
	// if either are dead, set dead flag, battlefield will cleanup
	if (m_currentHealth <= 0)
	{
		m_isDead = true;
	}
	if (target->m_currentHealth <= 0)
	{
		target->m_isDead = true;
	}
	// set has attacked flag
	m_hasAttacked = true;
}

// canAttack
/*
	Checks validated of desired attack
*/
bool dtn::EntityBattlefield::canAttack(std::shared_ptr<dtn::EntityBattlefield> runestone)
{
	// if different owner from target runestone and has not attacked
	if (m_owner != runestone->getOwner() && !m_hasAttacked)
	{
		int distance = dtn::Utilities::TileDistance(getBounds(), runestone->getBounds());
		// if in range
		if (distance <= m_range)
		{
			return true;
		}
	}
	return false;
}

// getTilePos
sf::Vector2i dtn::EntityBattlefield::getTilePos()
{
	return sf::Vector2i(m_bounds.left, m_bounds.top);
}

// getSize
sf::Vector2i dtn::EntityBattlefield::getSize()
{
	return sf::Vector2i(m_bounds.width, m_bounds.height);
}

// getBounds
sf::IntRect dtn::EntityBattlefield::getBounds()
{
	return m_bounds;
}

// getLos
int dtn::EntityBattlefield::getLos()
{
	return m_los;
}

// getOwner
int dtn::EntityBattlefield::getOwner()
{
	return m_owner;
}

// getSpeed
int dtn::EntityBattlefield::getSpeed()
{
	return m_speed;
}

// getRange
int dtn::EntityBattlefield::getRange()
{
	return m_range;
}

// setTilePos
void dtn::EntityBattlefield::setTilePos(sf::Vector2i tilePos)
{
	m_bounds.left = tilePos.x;
	m_bounds.top = tilePos.y;
}

// setSize
void dtn::EntityBattlefield::setSize(sf::Vector2i size)
{
	m_bounds.width = size.x;
	m_bounds.height = size.y;
}

// setBounds
void dtn::EntityBattlefield::setBounds(sf::IntRect bounds)
{
	m_bounds = bounds;
}

// setOwner
void dtn::EntityBattlefield::setOwner(int id)
{
	m_owner = id;
}

// setHasAttacked
void dtn::EntityBattlefield::setHasAttacked(bool f)
{
	m_hasAttacked = f;
}

// setHasMoved
void dtn::EntityBattlefield::setHasMoved(bool f)
{
	m_hasMoved = f;

	// update the entities move flag
	dtn::GlobalEventQueue::getInstance()->pushEvent(std::shared_ptr<dtn::Event>(
		new dtn::EventEntityMoveFlagChanged(m_entityID, m_hasMoved)));
}

// canMove
bool dtn::EntityBattlefield::canMove()
{
	return !m_hasMoved;
}

// isDead
bool dtn::EntityBattlefield::isDead()
{
	return m_isDead;
}