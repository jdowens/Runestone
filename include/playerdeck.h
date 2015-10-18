/*
	playerdeck.h
	Abstraction for a deck of runestones.
*/

#ifndef _PLAYERDECK_H
#define _PLAYERDECK_H

// c++ includes
#include<vector>
#include<memory>
#include<algorithm>
#include<chrono>
#include<random>

// sfml includes
#include<SFML/Graphics.hpp>

// dtn includes
#include "runestone.h"

namespace dtn
{
	class PlayerDeck
	{
	public:
		// constructor
		PlayerDeck(int id);

		// runestone functions
		void addRunestone(std::shared_ptr<dtn::Runestone> runestone);
		std::shared_ptr<dtn::Runestone> draw();
		void shuffle();
		
		// get/set
		int size();

		// debug render (not used)
		void render(sf::RenderWindow& window);
	private:
		int m_playerID;
		std::vector<std::shared_ptr<dtn::Runestone>> m_runestones;
	};
}
#endif