#include "runestone.h"

// initialize static instance count (needs to be session based...)
int dtn::Runestone::m_runestoneCount = 0; 

// constructor
dtn::Runestone::Runestone(dtn::RunestoneEntry entry) 
	: dtn::EntityBattlefield(m_runestoneCount++, dtn::Entity::EntityType::RUNESTONE)
{
	m_id = entry.m_id;
	m_renderableID = m_id;
	m_name = entry.m_name;
	m_maxHealth = entry.m_maxHealth;
	m_currentHealth = m_maxHealth;
	m_damage = entry.m_damage;
	m_range = entry.m_range;
	m_speed = entry.m_speed;
	m_los = entry.m_los;
	m_cost = entry.m_cost;
	m_bounds = sf::IntRect(-1,-1, 1, 1);
	m_owner = -1;
	m_isDead = false;
	m_hasMoved = false;
	m_hasAttacked = false;
	m_state = dtn::Runestone::state::UNINIT;
}

// constructor
/*
	This is the serial based constructor for building a runestone using data received over TCP comm.
	Have to send the runetone::toString() value for reconstruction
*/
dtn::Runestone::Runestone(std::string str)
	: dtn::EntityBattlefield(m_runestoneCount++, dtn::Entity::EntityType::RUNESTONE)
{
	std::stringstream ss(str);
	std::string word;
	ss >> word;
	int entityID;
	ss >> std::hex >> entityID >> std::dec;
	m_entityID = entityID;
	m_type = dtn::Entity::EntityType::RUNESTONE;
	ss >> word >> word;
	int ID;
	ss >> word >> ID;
	m_id = ID;
	int owner, cost;
	ss >> word >> owner >> word >> cost;
	m_owner = owner;
	m_cost = cost;
	ss >> word >> word;
	m_name = word;
	int mHealth, cHealth;
	ss >> word >> mHealth >> word >> cHealth;
	m_maxHealth = mHealth;
	m_currentHealth = cHealth;
	int damage, range;
	ss >> word >> damage >> word >> range;
	m_damage = damage;
	m_range = range;
	int speed, los;
	ss >> word >> speed >> word >> los;
	m_speed = speed;
	m_los = los;
	bool hMoved, hAttacked, iDead;
	ss >> word >> hMoved >> word >> hAttacked >> word >> iDead;
	m_hasMoved = hMoved;
	m_hasAttacked = hAttacked;
	m_isDead = iDead;
	int posX, posY;
	ss >> word >> posX >> posY;
	sf::Vector2i pos(posX, posY);
	m_bounds = sf::IntRect(-1, -1, 1, 1);
	ss >> word >> word;
	m_state = stringToState(word);
}

// print
void dtn::Runestone::print()
{
	printToStream(std::cout);
}

// toString
std::string dtn::Runestone::toString()
{
	std::stringstream ss;
	printToStream(ss);
	return ss.str();
}

std::string dtn::Runestone::toCondensedTooltip()
{
	std::stringstream ss;
	ss << "Name: " << m_name << "\tCost: " << m_cost << '\n';
	ss << "Health: " << m_currentHealth << '/' << m_maxHealth << '\n';
	ss << "Damage: " << m_damage << "\tRange: " << m_range << '\n';
	ss << "Speed: " << m_speed << "\tLine of Sight: " << m_los << '\n';
	return ss.str();
}

// getState
dtn::Runestone::state dtn::Runestone::getState()
{
	return m_state;
}

// setState
void dtn::Runestone::setState(dtn::Runestone::state state)
{
	m_state = state;
}

// getCost
int dtn::Runestone::getCost()
{
	return m_cost;
}

// getID
int dtn::Runestone::getID()
{
	return m_id;
}

// printToStream
void dtn::Runestone::printToStream(std::ostream& stream)
{
	stream << "ENTITY_ID: " << std::hex << std::setfill('0') << 
		std::setw(8) << m_entityID << std::dec << '\n';
	stream << "ENTITY_TYPE: " << Entity::entityTypeToString(m_type) << '\n';
	stream << "ID: " << m_id << '\n';
	stream << "OWNER: " << m_owner << ' ' << "COST: " << m_cost << '\n';
	stream << "NAME: " << m_name << '\n';
	stream << "MAX_HEALTH: " << m_maxHealth << ' ' << "CURRENT_HEALTH: " << m_currentHealth << '\n';
	stream << "DAMAGE: " << m_damage << ' ' << "RANGE: " << m_range << '\n';
	stream << "SPEED: " << m_speed << ' ' << "LOS: " << m_los << '\n';
	stream << "HAS_MOVED: " << m_hasMoved << ' ' << "HAS_ATTACKED: " << m_hasAttacked << '\n';
	stream << "IS_DEAD: " << m_isDead << '\n';
	stream << "TILE_POSITION: " << getTilePos().x << ' ' << getTilePos().y << '\n';
	stream << "STATE: " << stateToString(m_state) << '\n';
}

// stateToString
/*
	Needs to be updated when a state is added.
*/
std::string dtn::Runestone::stateToString(dtn::Runestone::state state)
{
	std::string ret = "";
	switch (state)
	{
	case dtn::Runestone::state::UNINIT : ret = "UNINIT"; break;
	case dtn::Runestone::state::IN_HAND : ret = "IN_HAND"; break;
	case dtn::Runestone::state::ON_BATTLEFIELD : ret = "ON_BATTLEFIELD"; break;
	case dtn::Runestone::state::SELECTED : ret = "SELECTED"; break;
	case dtn::Runestone::state::IN_DECK : ret = "IN_DECK"; break;
	}
	return ret;
}

// stringToState
/*
	Needs to be updated when a state is added.
*/
dtn::Runestone::state dtn::Runestone::stringToState(std::string str)
{
	dtn::Runestone::state ret = dtn::Runestone::state::UNINIT;
	if (str == "UNINIT")
		ret = dtn::Runestone::state::UNINIT;
	else if (str == "IN_HAND")
		ret = dtn::Runestone::state::IN_HAND;
	else if (str == "ON_BATTLEFIELD")
		ret = dtn::Runestone::state::ON_BATTLEFIELD;
	else if (str == "SELECTED")
		ret = dtn::Runestone::state::SELECTED;
	else if (str == "IN_DECK")
		ret = dtn::Runestone::state::IN_DECK;
	return ret;
}
