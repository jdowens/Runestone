/*
	battlefield.h
	This class serves as an abstraction for the game's battlefield area.
	It has the responsibility of holding control over all EntityBattlefields
	played to the battlefield.
*/

#ifndef _BATTLEFIELD_H
#define _BATTLEFIELD_H

// c++ includes
#include<iostream>
#include<vector>
#include<memory>

// SFML includes
#include<SFML/Graphics.hpp>
#include<SFML/System/Vector2.hpp>

// dtn includes
#include "entitybattlefield.h"
#include "runestone.h"
#include "utilities.h"
#include "playerbase.h"

namespace dtn
{
	class Battlefield
	{
	public :
		// constructor
		Battlefield(sf::Vector2i dimension);

		// entity control and validation functions
		void playEntityBattlefield(std::shared_ptr<EntityBattlefield> ent, sf::Vector2i position);
		bool canPlayEntityBattlefield(std::shared_ptr<EntityBattlefield> ent, sf::Vector2i position);
		void moveEntityBattlefield(std::shared_ptr<EntityBattlefield> ent, sf::Vector2i dest);
		void moveEntityBattlefield(sf::Vector2i source, sf::Vector2i dest);
		bool canMoveEntityBattlefield(std::shared_ptr<EntityBattlefield> ent, sf::Vector2i dest);
		bool canMoveEntityBattlefield(sf::Vector2i source, sf::Vector2i dest, int playerID);
		void attackEntityBattlefield(sf::Vector2i source, sf::Vector2i dest);
		bool canAttackEntityBattlefield(sf::Vector2i source, sf::Vector2i dest, int playerID);
		
		// pathfinding functions
		std::vector<sf::Vector2i> getValidMoveLocations(sf::Vector2i entPosition);

		// LOS functions
		std::vector<sf::Vector2i> getHiddenLocations(int playerID);
		bool isVisible(sf::Vector2i position, int playerID);

		// entity polling and reset functions
		std::shared_ptr<EntityBattlefield> getEntityBattlefieldAt(sf::Vector2i position);
		void dtn::Battlefield::resetEntityBattlefieldFlags();

		// update function (called once per frame)
		void update();

		// get/set
		sf::Vector2i getDimension();

		// helper functions

		// debug rendering function (NOT USED)
		void render(sf::RenderWindow& window, int playerID);

		// AI helper functions
		std::shared_ptr<EntityBattlefield> getFirstMoveableEntity(int playerID);
		std::shared_ptr<EntityBattlefield> getFirstAttackReadyEntity(int playerID);
		std::vector<std::shared_ptr<EntityBattlefield>> getAllMovableEntities(int playerID);
		std::vector<std::shared_ptr<dtn::EntityBattlefield>> getAllOwnedRunes(int playerID);
		sf::Vector2i pathToEnemyBase(std::shared_ptr<EntityBattlefield> ent);
		sf::Vector2i pathToSpace(std::shared_ptr<EntityBattlefield> ent, sf::Vector2i dest);
		std::vector<sf::Vector2i> getBorderingSpaces(sf::IntRect bounds);
		std::shared_ptr<dtn::EntityBattlefield> findPlayerBase(int playerID);
		sf::Vector2i closestSpace(std::vector<sf::Vector2i> list, sf::Vector2i dest);
		sf::Vector2i closestUnoccupiedSpace(std::vector<sf::Vector2i> list, sf::Vector2i dest);
		std::shared_ptr<dtn::EntityBattlefield> closestEnemy(std::vector<std::shared_ptr<dtn::EntityBattlefield>> list, 
			std::shared_ptr<dtn::EntityBattlefield> ent);
		std::shared_ptr<dtn::EntityBattlefield> closestEnemyInRange(std::shared_ptr<EntityBattlefield> ent);
		sf::Vector2i randomAvailablePlayLocation(int playerID);

	private :
		// w,h dimensions of board
		sf::Vector2i m_dimension;				
		// x,y,w,h dimensions of board
		sf::IntRect m_boardArea;			
		// bounding boxes for p1 and p2 valid play locations (index 1 and 2 respectively, 0 is void)
		std::vector<sf::IntRect> m_playLocations;	
		// vector of played EntityBattlefields
		std::vector<std::shared_ptr<EntityBattlefield>> m_placedEntityBattlefields;
		// pathfinding recursive function
		void determineValidMoveLocations(sf::Vector2i curPos, int distTraveled, int Range, std::vector<sf::Vector2i>& list);
	};
}

#endif