/*
	player.h
	An abstraction of a player in the game. Has the ability to control deck and hand.
*/

#ifndef _PLAYER_H
#define _PLAYER_H

// c++ includes
#include<string>
#include<sstream>
#include<iostream>
#include<memory>
#include<algorithm>

// sfml includes
#include<SFML/Graphics.hpp>

// dtn includes
#include "playerhand.h"
#include "playerdeck.h"
#include "runestone.h"
#include "event.h"
#include "globaleventqueue.h"

namespace dtn
{
	class Player
	{
	public :
		// constructor
		Player(int id);
		
		// deck building functions
		void loadDeckFromFile(std::string fileName);
		void draft();
		void addToDeck(std::shared_ptr<dtn::Runestone> runestone);
		
		// playing controls
		void shuffleDeck();
		bool draw();
		std::shared_ptr<dtn::EntityBattlefield> playRunestone(std::shared_ptr<dtn::Runestone> runestone);
		bool playRunestone(std::shared_ptr<dtn::Runestone> runestone, sf::Vector2i position,
			dtn::Battlefield& battlefield);
		bool playRunestone(int entityID, sf::Vector2i position, dtn::Battlefield& battlefield);
		bool moveRunestone(std::shared_ptr<dtn::Runestone> runestone, sf::Vector2i dest,
			dtn::Battlefield& battlefield);
		bool moveRunestone(sf::Vector2i source, sf::Vector2i dest, dtn::Battlefield& battlefield);
		bool attackRunestone(sf::Vector2i source, sf::Vector2i dest, dtn::Battlefield& battlefield);
		
		// mana controls
		void increaseMana(int n = 1);
		void resetCurrentMana();

		// convert to string
		std::string toString();

		// get/set
		bool holdingRunestone(int entityID);
		std::shared_ptr<dtn::Runestone> getRunestoneAt(sf::Vector2i position);
		std::shared_ptr<dtn::Runestone> getLastDrawn();
		int getDeckCount();
		sf::Vector2i getHandPosition();
		sf::Vector2i getHandPosition(int index);
		const std::vector<std::shared_ptr<dtn::Runestone>>& getHand();			

		// debug render
		void render(sf::RenderWindow& window);
	private :
		int m_playerID;					// player identification number
		int m_currentMana;				// current mana
		int m_maxMana;					// maximum mana
		void changeCurrentMana(int newAmount);		// interface to change mana value
		dtn::PlayerDeck m_deck;			// deck of runestones
		dtn::PlayerHand m_hand;			// hand of runestones
	};
}
#endif