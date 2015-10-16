/*
	runestone.h
	A container class for all of the runestone specific properties.
*/
#ifndef _RUNESTONE_H
#define _RUNESTONE_H

// c++ includes
#include<iostream>
#include<string>
#include<memory>
#include<sstream>
#include<ostream>

// sfml includes
#include<SFML/System/Vector2.hpp>

// dtn includes
#include "runestonedatabase.h"
#include "battlefield.h"
#include "entitybattlefield.h"

namespace dtn
{
	struct RunestoneEntry;

	class Runestone : public dtn::EntityBattlefield
	{
	public:
		// state of runestone
		typedef enum class state{UNINIT, IN_HAND, ON_BATTLEFIELD, SELECTED, IN_DECK /* NEED TO UPDATE STATIC FUNCTIONS! */};
		
		// constructors
		Runestone(dtn::RunestoneEntry entry);
		Runestone(std::string str);
		
		// virtual overrides
		virtual void print();
		virtual std::string toString();

		// get/set
		dtn::Runestone::state getState();
		void setState(dtn::Runestone::state state);
		int getCost();
		int getID();
	private:
		int m_id;
		static int m_runestoneCount;
		int m_cost;
		void printToStream(std::ostream& stream);
		state m_state;
		static std::string stateToString(dtn::Runestone::state state);
		static state stringToState(std::string);
	};
}

#endif