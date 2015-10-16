/*
	playerhand.h
	An abstraction for a hand of runestones.
*/

#ifndef _PLAYERHAND_H
#define _PLAYERHAND_H

// c++ includes
#include<vector>
#include<memory>

// sfml includes
#include<SFML/Graphics.hpp>

// dtn includes
#include "runestone.h"
#include "battlefield.h"

namespace dtn
{
	class PlayerHand
	{
	public:
		// constructor
		PlayerHand(int playerID);

		// runestone functions
		void addRunestone(std::shared_ptr<dtn::Runestone> runestone);
		bool containsRunestone(int entityID);
		std::shared_ptr<dtn::Runestone> getRunestoneAt(sf::Vector2i position);
		std::shared_ptr<dtn::Runestone> getRunestoneByEntityID(int entityID);
		std::shared_ptr<dtn::Runestone> getLastDrawn();
		std::shared_ptr<dtn::Runestone> playRunestone(std::shared_ptr<dtn::Runestone> runestone);
		
		// get/set
		const std::vector<std::shared_ptr<dtn::Runestone>>& getHand();		
		int getCount();
		sf::Vector2i getNextCardPosition();
		sf::Vector2i getCardPosition(int index);

		// debug render (not used)
		void render(sf::RenderWindow& window);
	private:
		int m_playerID;
		std::vector<std::shared_ptr<dtn::Runestone>> m_runestones;
	};
}

#endif