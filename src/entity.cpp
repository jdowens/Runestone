#include "entity.h"

// initialize count to 0 globally
// WARNING WARNING WARNING this needs to be changed to handle multiple sessions
int dtn::Entity::entityCount = 0;

// Two parameter consturctor
/*
	This constructor uses the subcount of the child class to initialize the
	global entity id for the entity.
*/
dtn::Entity::Entity(int count, dtn::Entity::EntityType type)
{
	// increase entity count
	entityCount++;
	// create entity id
	_Uint32t baseID = static_cast<_Uint32t>(type) << 24;
	m_entityID = count | baseID;
	m_type = type;
}

// constructor
/*
	Only increments entityCount, does nothing else.
*/
dtn::Entity::Entity()
{
	entityCount++;
}

// entityTypeToString
/*
	Converts an entity type to its string representation.
*/
std::string dtn::Entity::entityTypeToString(dtn::Entity::EntityType type)
{
	std::string ret = "";
	switch (type)
	{
	case dtn::Entity::EntityType::RUNESTONE: ret = "RUNESTONE"; break;
	case dtn::Entity::EntityType::PLAYERBASE: ret = "PLAYER_BASE"; break;
	case dtn::Entity::EntityType::UIELEMENT: ret = "UI_ELEMENT"; break;
	}
	return ret;
}

// getType
dtn::Entity::EntityType dtn::Entity::getType()
{
	return m_type;
}

// getEntityID
int dtn::Entity::getEntityID()
{
	return m_entityID;
}

// getRenderableID
int dtn::Entity::getRenderableID()
{
	return m_renderableID;
}

// destructor
dtn::Entity::~Entity()
{
	entityCount--;
}