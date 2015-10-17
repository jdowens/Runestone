#include "runestonedatabase.h"

// toString
/*
	Convert a runestone entry to a string.
*/
std::string dtn::RunestoneEntry::toString()
{
	std::stringstream ss;
	ss << "NAME: " << m_name << '\n';
	ss << "COST: " << m_cost << '\n';
	ss << "HEALTH: " << m_maxHealth << '\n';
	ss << "DAMAGE: " << m_damage << '\n';
	ss << "RANGE: " << m_range << '\n';
	ss << "SPEED: " << m_speed << '\n';
	ss << "LINE_OF_SIGHT: " << m_los << '\n';
	ss << "ID: " << m_id << '\n';
	return ss.str();
}

// set singleton instance to NULL
std::shared_ptr<dtn::RunestoneDatabase> dtn::RunestoneDatabase::m_instance = NULL;

// getInstance
/*
Create a new instance if not yet created and then return.
*/
std::shared_ptr<dtn::RunestoneDatabase> dtn::RunestoneDatabase::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = std::shared_ptr<dtn::RunestoneDatabase>(new dtn::RunestoneDatabase("Resources/database.csv"));
	}
	return m_instance;
}

// newRunestone
/*
	Create a dynamic new runestone and relinquish control.
*/
std::shared_ptr<dtn::Runestone> dtn::RunestoneDatabase::newRunestone(int id)
{
	return std::shared_ptr<dtn::Runestone>(new dtn::Runestone(m_database[id]));
}

// toString
/*
	Convert entire database to a string.
*/
std::string dtn::RunestoneDatabase::toString()
{
	std::stringstream ss;
	ss << "ID," << "NAME," << "HEALTH," << "DAMAGE," << "RANGE," 
		<< "SPEED," << "LOS," << "COST" << '\n';
	for (std::map<int, dtn::RunestoneEntry>::iterator it = m_database.begin();
		it != m_database.end(); ++it)
	{
		ss << it->second.m_id << ',' << it->second.m_name << ','
			<< it->second.m_maxHealth << ',' << it->second.m_damage << ','
			<< it->second.m_range << ',' << it->second.m_speed << ','
			<< it->second.m_los << ',' << it->second.m_cost << '\n';
	}
	return ss.str();
}

// generateWriteToFile
/*
	Randomly generate a bunch of runestones and write them to a file.
*/
void dtn::RunestoneDatabase::generateWriteToFile(std::string namesFileName, std::string outFileName)
{
	std::srand(std::time(NULL));
	std::ifstream inFile;
	inFile.open(namesFileName.c_str());
	std::ofstream outFile;
	outFile.open(outFileName.c_str());
	if (!inFile)
	{
		std::cout << "Failed to open input file dtn::RunestoneDatabase::generateWriteToFile...\n";
		exit(1);
	}
	if (!outFile)
	{
		std::cout << "Failed to open output file dtn::RunestoneDatabase::generateWriteToFile...\n";
		exit(1);
	}
	std::string word;
	int count = 0;
	while (inFile)
	{
		dtn::RunestoneEntry temp;
		inFile >> word;
		temp.m_id = count++;
		temp.m_name = word;
		temp.m_maxHealth = std::rand() % 10 + 1;
		temp.m_damage = std::rand() % 10 + 1;
		temp.m_range = std::rand() % 3 + 1;
		temp.m_speed = std::rand() % 10 + 1;
		temp.m_los = std::rand() % 10 + 1;
		temp.m_cost = calculateCost(temp);
		m_database[temp.m_id] = temp;
	}
	outFile << toString();
	inFile.clear();
	inFile.close();
	outFile.clear();
	outFile.close();
}

// getCount
int dtn::RunestoneDatabase::getCount()
{
	return m_database.size();
}

// getInfo
std::string dtn::RunestoneDatabase::getInfo(int id)
{
	return m_database[id].toString();
}

// calculateCost
int dtn::RunestoneDatabase::calculateCost(int h, int d, int r, int s, int los)
{
	// old formula
	// int cost = ((h * 5 + d * 5 + (r - 1) * 5 + (s - 5)*d + (los - 5)*h)/10);
	int cost = ((h * 3 + d * 3 + (r - 1) * 5 + (s - 5)*d + (los - 5)*h)/10);
	return cost == 0 ? 0 : cost;
}

// calculateCost
int dtn::RunestoneDatabase::calculateCost(dtn::RunestoneEntry rent)
{
	return calculateCost(rent.m_maxHealth, rent.m_damage, rent.m_range,
		rent.m_speed, rent.m_los);
}

// constructor
/*
Setup instance by loading all runestone properties from the database file.
*/
dtn::RunestoneDatabase::RunestoneDatabase(std::string fileName)
{
	std::ifstream file(fileName.c_str());

	if (!file)
	{
		std::cout << "FAILED TO OPEN DATABASE FILE IN RUNESTONE DATABASE..." << std::endl;
		exit(1);
	}

	file.ignore(256, '\n');
	std::string line;
	while (file)
	{
		RunestoneEntry temp;
		std::getline(file, line, '\n');
		if (line == "")
			break;
		std::stringstream ss(line);
		std::string token;
		std::vector<std::string> vecLine;
		while (std::getline(ss, token, ','))
			vecLine.push_back(token);
		temp.m_id = std::atoi(vecLine[0].c_str());
		temp.m_name = vecLine[1];
		temp.m_maxHealth = std::atoi(vecLine[2].c_str());
		temp.m_damage = std::atoi(vecLine[3].c_str());
		temp.m_range = std::atoi(vecLine[4].c_str());
		temp.m_speed = std::atoi(vecLine[5].c_str());
		temp.m_los = std::atoi(vecLine[6].c_str());
		temp.m_cost = calculateCost(temp);
		m_database[temp.m_id] = temp;
	}
}