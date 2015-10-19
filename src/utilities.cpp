#include "utilities.h"

int dtn::Utilities::WINDOW_WIDTH = 1280;
int dtn::Utilities::WINDOW_HEIGHT = 720;
int dtn::Utilities::PIXELS_PER_TILE_X = WINDOW_WIDTH / (2 * BOARD_LEFT + BOARD_WIDTH);
int dtn::Utilities::PIXELS_PER_TILE_Y = WINDOW_HEIGHT / (2 * BOARD_TOP + BOARD_HEIGHT);
bool dtn::Utilities::randInitialized = false;

// PixelToTile
/*
	Convert a vector in terms of pixels to a vector in terms of tiles.
*/
sf::Vector2i dtn::Utilities::PixelToTile(sf::Vector2i vec)
{
	return sf::Vector2i(vec.x / PIXELS_PER_TILE_X, vec.y / PIXELS_PER_TILE_Y);
}

// MouseToGlobalTile
/*
	Convert a mouse location to a tile location (taking into consideration player viewport).
*/
sf::Vector2i dtn::Utilities::MouseToGlobalTile(sf::Vector2i vec, int playerID)
{
	return LocalTileToGlobal(PixelToTile(vec), playerID);
}

// LocalTileToGlobal
/*
	Convert the local tile cooridinates to a player's local cooridnates.
*/
sf::Vector2i dtn::Utilities::LocalTileToGlobal(sf::Vector2i vec, int playerID)
{
	sf::Vector2i ret(0,0);
	if (playerID == 1)
	{
		ret = vec;
	}
	// if player 2, need to flip the y coordinate
	else if (playerID == 2)
	{
		ret.x = vec.x;
		ret.y = (WINDOW_HEIGHT / PIXELS_PER_TILE_Y) - vec.y - 1;
	}
	else
	{
		std::cout << "PLAYER ID UNDEFINED IN FUNCTION LOCALTILETOGLOBAL"
			<< std::endl;
	}
	return ret;
}

// LocalBoundsToGlobalPosition
/*
	Converts a set of boundaries to a localized position for a player viewport.
*/
sf::Vector2i dtn::Utilities::LocalBoundsToGlobalPosition(sf::IntRect bounds, int playerID)
{
	sf::Vector2i ret(0, 0);
	if (playerID == 1)
		ret = sf::Vector2i(bounds.left, bounds.top);
	// if player 2, need to flip y coordinate and use the midpoint of the y cooridnate to calculate flip
	// the midpoint of the y is used to flip because the object must be flipped through its horizontal axis
	// not through the axis attached to the top of the object
	else if (playerID == 2)
	{
		ret = LocalTileToGlobal(sf::Vector2i(bounds.left, bounds.top + bounds.height/2),
			playerID);
	}
	else
	{
		std::cout << "PLAYER ID UNDEFINED IN FUNCTION LOCALTILETOGLOBAL"
			<< std::endl;
	}
	return ret;
}

// TileToFloat
sf::Vector2f dtn::Utilities::TileToFloat(sf::Vector2i vec)
{
	return sf::Vector2f(static_cast<float>(vec.x*PIXELS_PER_TILE_X),
		static_cast<float>(vec.y*PIXELS_PER_TILE_Y));
}

// TileDistance
int dtn::Utilities::TileDistance(sf::Vector2i vec1, sf::Vector2i vec2)
{
	int distance = std::abs(vec2.x - vec1.x) +
		std::abs(vec2.y - vec1.y);
	return distance;
}

// TileDistance
/*
	Finds shortest distance between two IntRects.
*/
int dtn::Utilities::TileDistance(sf::IntRect rect1, sf::IntRect rect2)
{
	std::vector<sf::Vector2i> rect1Points, rect2Points;
	for (int i = 0; i < rect1.height; i++)
	{
		for (int j = 0; j < rect1.width; j++)
		{
			rect1Points.push_back(sf::Vector2i(
				rect1.left + j, rect1.top + i));
		}
	}

	for (int i = 0; i < rect2.height; i++)
	{
		for (int j = 0; j < rect2.width; j++)
		{
			rect2Points.push_back(sf::Vector2i(
				rect2.left + j, rect2.top + i));
		}
	}

	int distance = TileDistance(rect1Points.back(), rect2Points.back());
	while (!rect1Points.empty())
	{
		sf::Vector2i cur = rect1Points.back();
		for (std::vector<sf::Vector2i>::iterator it =
			rect2Points.begin(); it != rect2Points.end(); ++it)
		{
			int tempDistance = TileDistance(*it, cur);
			if (tempDistance < distance)
				distance = tempDistance;
		}
		rect1Points.pop_back();
	}
	return distance;
}

// TileDistance
int dtn::Utilities::TileDistance(sf::IntRect rect1, sf::Vector2i vec2)
{
	return TileDistance(rect1, sf::IntRect(vec2.x, vec2.y, 1, 1));
}

float dtn::Utilities::VectorDistance(sf::Vector2f vec1, sf::Vector2f vec2)
{
	float distance = std::sqrt(std::pow((vec2.x - vec1.x), 2.0f) +
		std::pow((vec2.y - vec1.y), 2.0));
	return distance;
}

// FloatVecToInt
sf::Vector2i dtn::Utilities::FloatVecToInt(sf::Vector2f vec)
{
	return sf::Vector2i(static_cast<int>(vec.x),
		static_cast<int>(vec.y));
}

// IntVecToFloat
sf::Vector2f dtn::Utilities::IntVecToFloat(sf::Vector2i vec)
{
	return sf::Vector2f(static_cast<float>(vec.x),
		static_cast<float>(vec.y));
}

// OnResized
void dtn::Utilities::OnResized(int w, int h)
{
	WINDOW_WIDTH = w;
	WINDOW_HEIGHT = h;
	PIXELS_PER_TILE_X = WINDOW_WIDTH / (2 * BOARD_LEFT + BOARD_WIDTH);
	PIXELS_PER_TILE_Y = WINDOW_HEIGHT / (2 * BOARD_TOP + BOARD_HEIGHT);
}

void dtn::Utilities::initRandom()
{
	std::srand(std::time(NULL));
	randInitialized = true;
}

float dtn::Utilities::randFloat(float min, float max)
{
	if (!randInitialized)
	{
		initRandom();
	}
	float random = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	float diff = max - min;
	float r = random*diff;
	return min + r;
}
