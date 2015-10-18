#include "battlefield.h"

// constructor
/*
	The one parameter constructor creates a battlefield of a dimension
	given by the single input Vector2i parameter.
*/
dtn::Battlefield::Battlefield(sf::Vector2i dimension)
{
	// setup battlefield dimensions
	m_dimension = dimension;
	m_boardArea = sf::IntRect(dtn::Utilities::BOARD_LEFT, dtn::Utilities::BOARD_TOP,
		m_dimension.x, m_dimension.y);
	// Setup play bounding boxes
	// void index 0
	sf::IntRect r0(0, 0, 0, 0);
	// player 1 index 1
	sf::IntRect r1(dtn::Utilities::BOARD_LEFT, m_dimension.y + 
		dtn::Utilities::BOARD_TOP - 1, m_dimension.x, 1);
	// played 2 index 2
	sf::IntRect r2(dtn::Utilities::BOARD_LEFT, dtn::Utilities::BOARD_TOP, m_dimension.x, 1);
	m_playLocations.push_back(r0);
	m_playLocations.push_back(r1);
	m_playLocations.push_back(r2);
}

// playEntityBattlefield
/*
	This function sets the location of the input shared_ptr entity to the input position Vector2i parameter,
	then pushes the entity onto the pack of the placedEntityBattlefields vector.
*/
void dtn::Battlefield::playEntityBattlefield(std::shared_ptr<dtn::EntityBattlefield> ent, sf::Vector2i position)
{
	ent->setTilePos(position);
	m_placedEntityBattlefields.push_back(ent);
}

// canPlayEntityBattlefield
/*
	This functions checks whether the input Vector2i is located within the input EntityBattlefield's owner's
	spawning location. It also checks to make sure there is no EntityBattlefield already occupying
	the input parameter position.
*/
bool dtn::Battlefield::canPlayEntityBattlefield(std::shared_ptr<dtn::EntityBattlefield> ent, sf::Vector2i position)
{
	if (m_playLocations[ent->getOwner()].contains(position) && getEntityBattlefieldAt(position) == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// moveEntityBattlefield
/*
	Updates an entities position and sets the moved flag on the entity to true.
*/
void dtn::Battlefield::moveEntityBattlefield(std::shared_ptr<dtn::EntityBattlefield> ent, sf::Vector2i dest)
{
	ent->setTilePos(dest);
	ent->setHasMoved(true);
}

// moveEntityBattlefield
/*
	Works off of two position vectors. If the entity at v2i source is valid, this entity is
	moved to v2i dest.
*/
void dtn::Battlefield::moveEntityBattlefield(sf::Vector2i source, sf::Vector2i dest)
{
	std::shared_ptr<EntityBattlefield> ent = getEntityBattlefieldAt(source);
	if (ent != NULL)
	{
		ent->setTilePos(dest);
		ent->setHasMoved(true);
	}
}

// canMoveEntityBattlefield
/*
	Checks the validity of a move on a given EntityBattlefield.
*/
bool dtn::Battlefield::canMoveEntityBattlefield(std::shared_ptr<dtn::EntityBattlefield> ent, sf::Vector2i dest)
{
	// if the destination is inside the board area and the entity can move
	if (m_boardArea.contains(dest) && ent->canMove())
	{
		// old absolute distance pathfinding
		/*std::shared_ptr<EntityBattlefield> destEnt = getEntityBattlefieldAt(dest);
		int distance = dtn::Utilities::TileDistance(ent->getBounds(), dest);
		// if destination is empty
		if (destEnt == NULL)
		{
			// if destination is within range
			if (distance <= ent->getSpeed())
			{
				return true;
			}
		}*/
		std::vector<sf::Vector2i> paths = getValidMoveLocations(ent->getTilePos());
		if (std::find(paths.begin(), paths.end(), dest) != paths.end())
		{
			return true;
		}
	}
	return false;
}

// canMoveEntityBattlefield
/*
	Checks the validity of a move using two input vectors and the id of the player who is initiating the move.
*/
bool dtn::Battlefield::canMoveEntityBattlefield(sf::Vector2i source, sf::Vector2i dest, int playerID)
{
	// grab entity at source
	std::shared_ptr<dtn::EntityBattlefield> ent = getEntityBattlefieldAt(source);
	// if source valid and entity can move
	if (ent != NULL && ent->canMove())
	{
		// if player actually owns entity
		if (ent->getOwner() == playerID)
		{
			// old absolute distance pathfinding
			/*std::shared_ptr<EntityBattlefield> destEnt = getEntityBattlefieldAt(dest);
			int distance = dtn::Utilities::TileDistance(ent->getBounds(), dest);
			// if dest is empty
			if (destEnt == NULL)
			{
				// if dest is within entity's range
				if (distance <= ent->getSpeed())
				{
					return true;
				}
			}*/
			std::vector<sf::Vector2i> paths = getValidMoveLocations(source);
			if (std::find(paths.begin(), paths.end(), dest) != paths.end())
			{
				return true;
			}
		}
	}
	return false;
}

// attackEntityBattlefield
/*
	Makes the entity at v2i source attack the entity at v2i dest.
*/
void dtn::Battlefield::attackEntityBattlefield(sf::Vector2i source, sf::Vector2i dest)
{
	// grab two entity references
	std::shared_ptr<dtn::EntityBattlefield> ent1 = getEntityBattlefieldAt(source);
	std::shared_ptr<dtn::EntityBattlefield> ent2 = getEntityBattlefieldAt(dest);
	// attack and update hasAttacked flag
	ent1->attack(ent2);
	ent1->setHasAttacked(true);
}

// canAttackEntityBattlefield
/*
	Checks the validity of a given attack initiated by the player corresponding to playerID.
*/
bool dtn::Battlefield::canAttackEntityBattlefield(sf::Vector2i source, sf::Vector2i dest, int playerID)
{
	// grab two entities
	std::shared_ptr<dtn::EntityBattlefield> ent1 = getEntityBattlefieldAt(source);
	std::shared_ptr<dtn::EntityBattlefield> ent2 = getEntityBattlefieldAt(dest);
	// if both entities valid
	if (ent1 != NULL && ent2 != NULL)
	{
		// if ent1 can attack still (hasAttacked flag not set)
		// and playerID owns ent1
		if (ent1->canAttack(ent2) && ent1->getOwner() == playerID)
		{
			return true;
		}
	}
	return false;
}

std::vector<sf::Vector2i> dtn::Battlefield::getValidMoveLocations(sf::Vector2i entPosition)
{
	std::vector<sf::Vector2i> ret;
	auto ent = getEntityBattlefieldAt(entPosition);
	if (ent.get() != NULL && ent->getSpeed() > 0)
	{
		int distTraveled = 0;
		determineValidMoveLocations(entPosition, distTraveled, ent->getSpeed(), ret);
	}
	return ret;
}

// getEntityBattlefieldAt
/*
	Grab the entity at a given vector.
*/
std::shared_ptr<dtn::EntityBattlefield> dtn::Battlefield::getEntityBattlefieldAt(sf::Vector2i position)
{
	// the return pointer
	std::shared_ptr<dtn::EntityBattlefield> ret;
	for (std::vector<std::shared_ptr<dtn::EntityBattlefield>>::iterator it =
		m_placedEntityBattlefields.begin();	it != m_placedEntityBattlefields.end(); ++it)
	{
		// if current entity's bounds contains the v2i position
		if ((*it)->getBounds().contains(position))
		{
			// return pointer is current entity
			ret = (*it);
			break;
		}
	}
	// return default constructed shared ptr if no entity found
	return ret;
}

// resetEntityBattlefieldFlags
/*
	Iterate through every entity on the battlefield and reset their flags.
*/
void dtn::Battlefield::resetEntityBattlefieldFlags()
{
	for (std::vector<std::shared_ptr<dtn::EntityBattlefield>>::iterator it =
		m_placedEntityBattlefields.begin(); it != m_placedEntityBattlefields.end(); ++it)
	{
		if ((*it)->getType() == dtn::Entity::EntityType::RUNESTONE)
		{
			(*it)->setHasAttacked(false);
			(*it)->setHasMoved(false);
		}
	}
}

// update
/*
	Performs a sweep of the board. If any entity is dead, removes them.
*/
void dtn::Battlefield::update()
{
	for (std::vector<std::shared_ptr<dtn::EntityBattlefield>>::iterator it =
		m_placedEntityBattlefields.begin(); it != m_placedEntityBattlefields.end();)
	{
		if ((*it)->isDead())
		{
			it = m_placedEntityBattlefields.erase(it);
		}
		else
		{
			++it;
		}
	}
}

// getDimension
/*
	Return the dimensions of the battlefield.
*/
sf::Vector2i dtn::Battlefield::getDimension()
{
	return m_dimension;
}

std::vector<sf::Vector2i> dtn::Battlefield::getHiddenLocations(int playerID)
{
	std::vector<sf::Vector2i> ret;
	for (int x = dtn::Utilities::BOARD_LEFT; x < dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT; x++)
	{
		for (int y = dtn::Utilities::BOARD_TOP; y < dtn::Utilities::BOARD_HEIGHT + dtn::Utilities::BOARD_TOP; y++)
		{
			sf::Vector2i tmp(x, y);
			if (!isVisible(tmp, playerID))
				ret.push_back(tmp);
		}
	}
	return ret;
}

// isVisible
/*
	Check if a given v2i position is visible by a given player corresponding to playerID.
*/
bool dtn::Battlefield::isVisible(sf::Vector2i position, int playerID)
{
	// iterate through every EntityBattlefield
	for (std::vector<std::shared_ptr<dtn::EntityBattlefield>>::iterator it = m_placedEntityBattlefields.begin();
		it != m_placedEntityBattlefields.end(); ++it)
	{
		// if owned by playerID
		if ((*it)->getOwner() == playerID)
		{
			// check distance between current entity and input position
			int distance = dtn::Utilities::TileDistance((*it)->getBounds(), position);
			// if current entity can see location, return true
			if (distance <= (*it)->getLos())
			{
				return true;
			}
		}
	}
	return false;
}

// debug rendering (NOT USED)
void dtn::Battlefield::render(sf::RenderWindow& window, int playerID)
{
	sf::CircleShape circle(static_cast<float>(dtn::Utilities::PIXELS_PER_TILE_X) / 2.f);
	for (std::vector<std::shared_ptr<dtn::EntityBattlefield>>::iterator it =
		m_placedEntityBattlefields.begin();	it != m_placedEntityBattlefields.end(); ++it)
	{
		if ((*it)->getOwner() == playerID)
		{
			sf::Vector2f localPosIt = dtn::Utilities::TileToFloat(
				dtn::Utilities::LocalTileToGlobal((*it)->getTilePos(), playerID));
			circle.setPosition(localPosIt);
			circle.setFillColor(sf::Color::Blue);
			window.draw(circle);
			for (std::vector<std::shared_ptr<dtn::EntityBattlefield>>::iterator it2 =
				m_placedEntityBattlefields.begin();	it2 != m_placedEntityBattlefields.end(); ++it2)
			{
				if ((*it2)->getOwner() != playerID)
				{
					int distance = dtn::Utilities::TileDistance((*it)->getBounds(), (*it2)->getBounds());
					if (distance <= (*it)->getLos())
					{
						sf::Vector2f localPosIt2 = dtn::Utilities::TileToFloat(
							dtn::Utilities::LocalTileToGlobal((*it2)->getTilePos(), playerID));
						circle.setPosition(localPosIt2);
						circle.setFillColor(sf::Color::Green);
						window.draw(circle);
					}
				}
			}
		}
	}
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(dtn::Utilities::PIXELS_PER_TILE_X, dtn::Utilities::PIXELS_PER_TILE_Y));
	rect.setFillColor(sf::Color(0, 0, 0, 128));
	for (int i = dtn::Utilities::BOARD_LEFT;
		i < dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT; i++)
	{
		for (int j = dtn::Utilities::BOARD_TOP; j < dtn::Utilities::BOARD_HEIGHT +
			dtn::Utilities::BOARD_TOP; j++)
		{
			sf::Vector2i coords = dtn::Utilities::LocalTileToGlobal(sf::Vector2i(i, j), playerID);
			if (!isVisible(sf::Vector2i(i, j), playerID))
			{
				rect.setPosition(sf::Vector2f(coords.x*dtn::Utilities::PIXELS_PER_TILE_X,
					coords.y*dtn::Utilities::PIXELS_PER_TILE_Y));
				window.draw(rect);
			}

		}
	}
}

void dtn::Battlefield::determineValidMoveLocations(sf::Vector2i curPos, int distTraveled, int range, std::vector<sf::Vector2i>& list)
{
	sf::Vector2i left(curPos.x - 1, curPos.y);
	sf::Vector2i right(curPos.x + 1, curPos.y);
	sf::Vector2i up(curPos.x, curPos.y - 1);
	sf::Vector2i down(curPos.x, curPos.y + 1);
	// check left
	if (left.x >= dtn::Utilities::BOARD_LEFT && getEntityBattlefieldAt(sf::Vector2i(left.x, left.y)).get() == NULL)
	{
		if (std::find(list.begin(), list.end(), sf::Vector2i(left.x, left.y)) == list.end())
		{
			list.push_back(sf::Vector2i(left.x, left.y));
		}
		if (distTraveled + 1 < range)
		{
			determineValidMoveLocations(left, distTraveled + 1, range, list);
		}
	}
	// check right
	if (right.x < (dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT) && getEntityBattlefieldAt(sf::Vector2i(right.x, right.y)).get() == NULL)
	{
		if (std::find(list.begin(), list.end(), sf::Vector2i(right.x, right.y)) == list.end())
		{
			list.push_back(sf::Vector2i(right.x, right.y));
		}
		if (distTraveled + 1 < range)
		{
			determineValidMoveLocations(right, distTraveled + 1, range, list);
		}
	}
	// check up
	if (up.y >= dtn::Utilities::BOARD_TOP && getEntityBattlefieldAt(sf::Vector2i(up.x, up.y)).get() == NULL)
	{
		if (std::find(list.begin(), list.end(), sf::Vector2i(up.x, up.y)) == list.end())
		{
			list.push_back(sf::Vector2i(up.x, up.y));
		}
		if (distTraveled + 1 < range)
		{
			determineValidMoveLocations(up, distTraveled + 1, range, list);
		}
	}
	// check down
	if (down.y < (dtn::Utilities::BOARD_HEIGHT + dtn::Utilities::BOARD_TOP) && getEntityBattlefieldAt(sf::Vector2i(down.x, down.y)).get() == NULL)
	{
		if (std::find(list.begin(), list.end(), sf::Vector2i(down.x, down.y)) == list.end())
		{
			list.push_back(sf::Vector2i(down.x, down.y));
		}
		if (distTraveled + 1 < range)
		{
			determineValidMoveLocations(down, distTraveled + 1, range, list);
		}
	}
}
