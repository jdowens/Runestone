#include "player.h"

// constructor
dtn::Player::Player(int id)
	: m_deck(id), m_hand(id)
{
	m_playerID = id;
	m_maxMana = 0;
	changeCurrentMana(m_maxMana);
}

// loadDeckFromFile
/*
Load a deck from a file (list of runestone IDs).
*/
void dtn::Player::loadDeckFromFile(std::string fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());
	if (!file)
	{
		std::cout << "FAILED TO OPEN FILE IN PLAYERVIEW::LOADDECKFROMFILE\n" << std::endl;
	}
	while (!file.eof())
	{
		int ID;
		file >> ID;
		addToDeck(dtn::RunestoneDatabase::getInstance()->newRunestone(ID));
	}
}

// draft
/*
Arena style deck building (terminal based).
*/
void dtn::Player::draft()
{
	std::srand(std::time(NULL));
	for (int i = 0; i < 30; i++)
	{
		std::cout << "Select (1), (2), (3):\n\n";
		int sel1, sel2, sel3;
		int choice;
		int size = dtn::RunestoneDatabase::getInstance()->getCount();
		sel1 = std::rand() % size;
		sel2 = std::rand() % size;
		sel3 = std::rand() % size;
		std::cout << "(1):\n";
		std::cout << dtn::RunestoneDatabase::getInstance()->getInfo(sel1);
		std::cout << "\n\n";
		std::cout << "(2):\n";
		std::cout << dtn::RunestoneDatabase::getInstance()->getInfo(sel2);
		std::cout << "\n\n";
		std::cout << "(3):\n";
		std::cout << dtn::RunestoneDatabase::getInstance()->getInfo(sel3);
		std::cout << "\n\n";
		std::cout << "CHOICE: ";
		std::cin >> choice;
		while (choice <= 0 || choice >= 4)
		{
			std::cout << "INVALID CHOICE, RE-ENTER: ";
			std::cin >> choice;
		}
		switch (choice)
		{
		case 1: m_deck.addRunestone(dtn::RunestoneDatabase::getInstance()->newRunestone(sel1));
			break;
		case 2: m_deck.addRunestone(dtn::RunestoneDatabase::getInstance()->newRunestone(sel2));
			break;
		case 3: m_deck.addRunestone(dtn::RunestoneDatabase::getInstance()->newRunestone(sel3));
			break;
		}
		std::cout << "\n\n\n\n\n";
	}
	m_deck.shuffle();
}

// addToDeck
/*
Adds a specific runestone to a players deck.
*/
void dtn::Player::addToDeck(std::shared_ptr<dtn::Runestone> runestone)
{
	m_deck.addRunestone(runestone);
}

// draw
/*
	Draws a runestone and sets the runestones state to IN_HAND
*/
bool dtn::Player::draw()
{
	std::shared_ptr<Runestone> temp = m_deck.draw();
	if (m_hand.getCount() < 10)
	{
		if (temp != NULL)
		{
			temp->setState(dtn::Runestone::state::IN_HAND);
			m_hand.addRunestone(temp);
			return true;
		}
	}
	return false;
}

// playRunestone
/*
	Relinquishes control of a runestone and subtracts from the player's mana count.
*/
std::shared_ptr<dtn::EntityBattlefield> dtn::Player::playRunestone(std::shared_ptr<dtn::Runestone> runestone)
{
	changeCurrentMana(m_currentMana - runestone->getCost());
	return m_hand.playRunestone(runestone);
}

// playRunestone
/*
	Plays a runestone to an input battlefield (if the runestone can be played).
*/
bool dtn::Player::playRunestone(std::shared_ptr<dtn::Runestone> runestone, sf::Vector2i position,
	dtn::Battlefield& battlefield)
{
	// ask battlefield if spot can be played into, check if enough mana
	if (battlefield.canPlayEntityBattlefield(runestone, position) &&
		runestone->getCost() <= m_currentMana)
	{
		// relinquish control of runestone
		battlefield.playEntityBattlefield(playRunestone(runestone), position);
		return true;
	}
	return false;
}

// playRunestone
/*
	Plays a runestone to an input battlefield by entityID.
*/
bool dtn::Player::playRunestone(int entityID, sf::Vector2i position, dtn::Battlefield& battlefield)
{
	std::shared_ptr<dtn::Runestone> rune = m_hand.getRunestoneByEntityID(entityID);
	if (rune != NULL)
	{
		return playRunestone(rune, position, battlefield);
	}
	return false;
}

// moveRunestone
/*
	Ask input battlefield if a runestone can be moved in a certain manner. Then performs move.
*/
bool dtn::Player::moveRunestone(std::shared_ptr<dtn::Runestone> runestone, sf::Vector2i dest,
	dtn::Battlefield& battlefield)
{
	if (battlefield.canMoveEntityBattlefield(runestone, dest))
	{
		battlefield.moveEntityBattlefield(runestone, dest);
		return true;
	}
	return false;
}

// moveRunestone
/*
	Performs move operation on runestone given a source vector (instead of pointer to runestone).
*/
bool dtn::Player::moveRunestone(sf::Vector2i source, sf::Vector2i dest,
	dtn::Battlefield& battlefield)
{
	if (battlefield.canMoveEntityBattlefield(source, dest, m_playerID))
	{
		battlefield.moveEntityBattlefield(source, dest);
		return true;
	}
	return false;
}

// attackRunestone
/*
	Causes battle between two runestones (if battle can occur).
*/
bool dtn::Player::attackRunestone(sf::Vector2i source, sf::Vector2i dest, dtn::Battlefield& battlefield)
{
	if (battlefield.canAttackEntityBattlefield(source, dest, m_playerID))
	{
		battlefield.attackEntityBattlefield(source, dest);
		return true;
	}
	return false;
}

// increaseMana
/*
	Max limit currently set to 10.
*/
void dtn::Player::increaseMana(int n)
{
	m_maxMana += n;
	if (m_maxMana > 10)
	{
		m_maxMana = 10;
	}
}

// resetCurrentMana
/*
	Resets a players mana (to max value).
*/
void dtn::Player::resetCurrentMana()
{
	changeCurrentMana(m_maxMana);
}

// toString
/*
	Used to convert a player to tooltip info.
*/
std::string dtn::Player::toString()
{
	std::stringstream ss;
	ss << "PLAYER_ID: " << m_playerID << '\n';
	ss << "MANA: " << m_currentMana << '/' << m_maxMana << '\n';
	ss << "CARDS_IN_DECK: " << m_deck.size() << '\n';
	return ss.str();
}

// holdingRunestone
/*
Checks if the runestone corresponding to entityID lays in the players hand.
*/
bool dtn::Player::holdingRunestone(int entityID)
{
	return m_hand.containsRunestone(entityID);
}

// getRunestoneAt
/*
grabs the runestone at a given position (from players hand)
*/
std::shared_ptr<dtn::Runestone> dtn::Player::getRunestoneAt(sf::Vector2i position)
{
	std::shared_ptr<Runestone> ret;
	ret = m_hand.getRunestoneAt(position);
	return ret;
}

// getLastDrawn
/*
Asks the hand which runestone it last drew.
*/
std::shared_ptr<dtn::Runestone> dtn::Player::getLastDrawn()
{
	return m_hand.getLastDrawn();
}

// getDeckCount
int dtn::Player::getDeckCount()
{
	return m_deck.size();
}

// getHandPosition
/*
	Asks hand where the next card would be placed (location wise).
*/
sf::Vector2i dtn::Player::getHandPosition()
{
	return m_hand.getNextCardPosition();
}

// getHandPosition
/*
	Asks hand where a particular card would go (based on index into hands vector of runestones).
*/
sf::Vector2i dtn::Player::getHandPosition(int index)
{
	return m_hand.getCardPosition(index);
}

// getHand
const std::vector<std::shared_ptr<dtn::Runestone>>& dtn::Player::getHand()
{
	return m_hand.getHand();
}

// render
/*
Outdated debug render.
*/
void dtn::Player::render(sf::RenderWindow& window)
{
	m_deck.render(window);
	m_hand.render(window);
}

// changeCurrentMana
/*
	Interface to change the mana of the player (includes sending an event that it has
	changed).
*/
void dtn::Player::changeCurrentMana(int amount)
{
	m_currentMana = amount;
	if (m_currentMana > m_maxMana)
		m_currentMana = m_maxMana;
	else if (m_currentMana < 0)
		m_currentMana = 0;
	dtn::GlobalEventQueue::getInstance()->pushEvent(std::shared_ptr<dtn::Event>(
		new dtn::EventManaChanged(m_playerID, m_currentMana)));
}