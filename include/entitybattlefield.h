/*
	entitybattlefield.h
	This class serves as a container for all of the information necessary to describe an EntityBattlefield
*/

#ifndef _ENTITYBATTLEFIELD_H
#define _ENTITYBATTLEFIELD_H

#include "entity.h"
#include "utilities.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include<memory>

namespace dtn
{
	class EntityBattlefield : public Entity
	{
	public :
		// constructors
		EntityBattlefield(int count, Entity::EntityType type);
		EntityBattlefield();

		// virtual overrides
		virtual void print() = 0;
		virtual std::string toString() = 0;

		// attack functions
		void attack(std::shared_ptr<dtn::EntityBattlefield> target);
		bool canAttack(std::shared_ptr<dtn::EntityBattlefield> runestone);

		// get/set
		sf::Vector2i getTilePos();
		sf::Vector2i getSize();
		sf::IntRect getBounds();
		int getLos();
		int getOwner();
		int getSpeed();
		int getRange();
		void setTilePos(sf::Vector2i tilePos);
		void setSize(sf::Vector2i size);
		void setBounds(sf::IntRect bounds);
		void setOwner(int id);
		void setHasAttacked(bool f);
		void setHasMoved(bool f);
		bool canMove();
		bool isDead();
	protected :
		std::string m_name;	
		int m_maxHealth;
		int m_currentHealth;
		int m_damage;
		int m_range;
		int m_speed;
		int m_los;
		int m_owner;
		bool m_isDead;
		bool m_hasMoved;
		bool m_hasAttacked;
		//sf::Vector2i m_tilePos;
		sf::IntRect m_bounds;

		// global count of number of battlefieldEntities
		static int m_battlefieldEntityCount;
	};
}

#endif