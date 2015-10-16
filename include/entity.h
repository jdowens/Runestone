/*
	entity.h
	This is the class definition of the entity type. This is essentially a global
	representation of anything in the game (UIELEMENT, RUNESTONE, PLAYERBASE, etc.).
*/

#ifndef _ENTITY_H
#define _ENTITY_H

// c++ includes
#include<string>
#include<iostream>
#include<iomanip>

namespace dtn
{
	class Entity
	{
	public :
		// enumerated type for type of entity
		typedef enum class EntityType : unsigned char 
		{
			RUNESTONE = 0x00, 
			PLAYERBASE = 0x01,
			UIELEMENT = 0x02
			// REMEBER TO UPDATE STATIC entityTypeToString FUNCTION!
		};

		// constructors
		Entity(int count, EntityType type);
		Entity();

		// virtual functions for override
		virtual void print() = 0;
		virtual std::string toString() = 0;

		// static functions
		// must be updated with each addition to the EntityType class
		static std::string entityTypeToString(EntityType type);

		// get/set
		EntityType getType();
		int getEntityID();
		int getRenderableID();

		// destructor
		~Entity();
	protected :
		static int entityCount;				// total count of entities in given session
		EntityType m_type;					// type of entity
		int m_entityID;						// global entity ID (synced across servers/clients)
		int m_renderableID;					// assigned as reference to Entity's spritesheet
	};
}
#endif