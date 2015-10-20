#include "playerbase.h"

// initialize instance count to 0 (needs to change to handle multiple sessions)
int dtn::PlayerBase::m_playerBaseCount = 0;

// constructor
/*
	Sets up the default player base.
*/
dtn::PlayerBase::PlayerBase(int owner, sf::Vector2i tilePos)
	: EntityBattlefield(m_playerBaseCount, dtn::Entity::EntityType::PLAYERBASE)
{
	m_playerBaseCount++;
	m_owner = owner;
	m_maxHealth = 30;
	m_currentHealth = m_maxHealth;
	m_damage = 0;
	m_range = 0;
	m_speed = 0;
	m_los = 1;
	m_isDead = false;
	m_hasMoved = false;
	m_hasAttacked = false;
	m_bounds = sf::IntRect(tilePos.x, tilePos.y, 2, 2);
	m_renderableID = 0;
}

// print
/*
	Print base info to the console.
*/
void dtn::PlayerBase::print()
{
	std::cout << "ENTITY_ID: " << std::hex << std::setfill('0') <<
		std::setw(8) << m_entityID << std::dec << '\n';
	std::cout << "ENTITY_TYPE: " << Entity::entityTypeToString(m_type) << '\n';
	std::cout << "OWNER: " << m_owner << '\n';
	std::cout << "MAX_HEALTH: " << m_maxHealth << ' ' << "CURRENT_HEALTH: " << m_currentHealth << '\n';
}

// toString
/*
	Convert the base to a string (for tooltip info).
*/
std::string dtn::PlayerBase::toString()
{
	std::stringstream ss;
	ss << "ENTITY_ID: " << std::hex << std::setfill('0') <<
		std::setw(8) << m_entityID << std::dec << '\n';
	ss << "ENTITY_TYPE: " << Entity::entityTypeToString(m_type) << '\n';
	ss << "OWNER: " << m_owner << '\n';
	ss << "MAX_HEALTH: " << m_maxHealth << ' ' << "CURRENT_HEALTH: " << m_currentHealth << '\n';

	return ss.str();
}

	std::string dtn::PlayerBase::toCondensedTooltip()
	{
		std::stringstream ss;
		ss << "Player " << m_owner << "'s Base\n";
		ss << "Health: " << m_currentHealth << '/' << m_maxHealth << '\n';
		return ss.str();
	}
