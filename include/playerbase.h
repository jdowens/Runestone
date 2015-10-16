/*
	playerbase.h
	An abstraction for the player's keep.
*/

#ifndef _PLAYERBASE_H
#define _PLAYERBASE_H

// c++ includes
#include<iostream>
#include<sstream>

// dtn includes
#include "entitybattlefield.h"

namespace dtn
{
	class PlayerBase : public EntityBattlefield
	{
	public :
		// constructor
		PlayerBase(int owner, sf::Vector2i tilePos);

		// virtual overrides
		virtual void print();
		virtual std::string toString();
	private :
		// global instance count
		static int m_playerBaseCount;
	};
}


#endif