/*
	tooltip.h
	A simple renderable tooltip.
*/
#ifndef _TOOLTIP_H
#define _TOOLTIP_H

// c++ includes
#include<string>
#include<algorithm>

// sfml includes
#include<SFML/System/Vector2.hpp>
#include<SFML/Graphics/Rect.hpp>
#include<SFML/Graphics.hpp>

// dtn includes
#include "utilities.h"

namespace dtn
{
	class Tooltip
	{
	public:
		// constructor
		Tooltip();

		// update function
		void update(sf::Vector2i pos, std::string s, bool youAreOwner);
		
		// get/set
		void setVisible();
		void setInvisible();
		void setLocation(sf::Vector2i pos);
		void setText(std::string text);
		
		// draw to window
		void render(sf::RenderWindow& window);
	private:
		sf::IntRect m_rect;
		void resize();
		bool m_visible;
		const int FONT_SIZE = 14;
		const int FONT_SIZE_PIXELS = 22;
		sf::Font m_font;
		sf::Text m_text;
		sf::Color m_rectBackgroundColor;
		size_t stringWidth(std::string s);
	};
}
#endif