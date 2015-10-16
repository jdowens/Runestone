/*
	runestonedatabase.h
	A factory for creating runestones.

	This is a singleton class.
*/
#ifndef _RUNESTONEDATABASE_H
#define _RUNESTONEDATABASE_H

// c++ includes
#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<memory>
#include<cstdlib>
#include<sstream>

// dtn includes
#include "runestone.h"

namespace dtn
{
	class Runestone;

	// base container for holding all runestone properties
	struct RunestoneEntry
	{
		int m_id;
		std::string m_name;
		int m_maxHealth;
		int m_damage;
		int m_range;
		int m_speed;
		int m_los;
		int m_cost;
		std::string toString();
	};

	class RunestoneDatabase
	{
	public:
		// singleton getInstance
		static std::shared_ptr<dtn::RunestoneDatabase> getInstance();

		// runestone functions
		std::shared_ptr<dtn::Runestone> newRunestone(int id);

		// convert database to a string
		std::string toString();

		// generate a brand new database and write it to a file
		void generateWriteToFile(std::string namesFile, std::string outFile);

		// get/set
		int getCount();

		// get info for a particular runestone id
		std::string getInfo(int id);
	private:
		// calculate the cost of a runestone
		int calculateCost(int h, int d, int r, int s, int los);
		int calculateCost(dtn::RunestoneEntry rent);
		std::map<int, dtn::RunestoneEntry> m_database;
		RunestoneDatabase(std::string fileName);
		static std::shared_ptr<dtn::RunestoneDatabase> m_instance;
	};
}

#endif