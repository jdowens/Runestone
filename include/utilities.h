/*
	utilities.h
	A collection of utility functions.
*/
#ifndef _UTILITIES_H
#define _UTILITIES_H

// c++ includes
#include<iostream>
#include<vector>
#include<cmath>

// sfml includes
#include<SFML/System/Vector2.hpp>
#include<SFML/Graphics/Rect.hpp>

namespace dtn
{
	class Utilities
	{
	public :
		static const int BOARD_WIDTH = 16;
		static const int BOARD_HEIGHT = 16;
		static const int BOARD_TOP = 1;
		static const int BOARD_LEFT = 1;
		static int WINDOW_WIDTH;
		static int WINDOW_HEIGHT;
		static int PIXELS_PER_TILE_X;
		static int PIXELS_PER_TILE_Y;
		static sf::Vector2i PixelToTile(sf::Vector2i vec);
		static sf::Vector2i MouseToGlobalTile(sf::Vector2i vec, int playerID);
		static sf::Vector2i LocalTileToGlobal(sf::Vector2i vec, int playerID);
		static sf::Vector2i LocalBoundsToGlobalPosition(sf::IntRect bounds, int playerID);
		static sf::Vector2f TileToFloat(sf::Vector2i vec);
		static int TileDistance(sf::Vector2i vec1, sf::Vector2i vec2);
		static int TileDistance(sf::IntRect rect1, sf::IntRect rect2);
		static int TileDistance(sf::IntRect rect1, sf::Vector2i vec2);
		static sf::Vector2i FloatVecToInt(sf::Vector2f vec);
		static sf::Vector2f IntVecToFloat(sf::Vector2i vec);
		static void OnResized(int w, int h);
	};
}
#endif