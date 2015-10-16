#include "tooltip.h"

// constructor
dtn::Tooltip::Tooltip()
{
	m_visible = false;
	m_rect = sf::IntRect(0, 0, 0, 0);
	m_font.loadFromFile("Resources/source-code-pro/SourceCodePro-Black.otf");
	m_text.setFont(m_font);
	m_text.setString("");
	m_text.setCharacterSize(FONT_SIZE);
	m_text.setColor(sf::Color::Red);
}

// update
/*
	Set the properties of the tooltip.
*/
void dtn::Tooltip::update(sf::Vector2i pos, std::string s)
{
	setText(s);
	setLocation(pos);
}

// setVisible
void dtn::Tooltip::setVisible()
{
	m_visible = true;
}

// setInvisible
void dtn::Tooltip::setInvisible()
{
	m_visible = false;
}

// setLocation
void dtn::Tooltip::setLocation(sf::Vector2i pos)
{
	// flip based on quadrant
	if (pos.x < dtn::Utilities::WINDOW_WIDTH / 2)
		m_rect.left = pos.x;
	else
		m_rect.left = pos.x - m_rect.width;
	if (pos.y < dtn::Utilities::WINDOW_HEIGHT / 2)
		m_rect.top = pos.y;
	else
		m_rect.top = pos.y - m_rect.height;
	m_text.setPosition(static_cast<float>(m_rect.left), static_cast<float>(m_rect.top));
}

// setText
void dtn::Tooltip::setText(std::string text)
{
	m_text.setString(text);
	m_rect.height = (std::count(text.begin(), text.end(), '\n'))*FONT_SIZE_PIXELS;
	m_rect.width = stringWidth(text)*FONT_SIZE_PIXELS/2;
}

// render
void dtn::Tooltip::render(sf::RenderWindow& window)
{
	if (m_visible)
	{
		sf::RectangleShape rect(sf::Vector2f(static_cast<float>(m_rect.width),
			static_cast<float>(m_rect.height)));
		rect.setPosition(static_cast<float>(m_rect.left),
			static_cast<float>(m_rect.top));
		rect.setFillColor(sf::Color::White);
		window.draw(rect);
		window.draw(m_text);
	}
}

// stringWidth
/*
	Calculates the width of a string (widest line).
*/
size_t dtn::Tooltip::stringWidth(std::string s)
{
	size_t p1 = 0;
	size_t p2 = 0;
	size_t curLength = 0;
	size_t maxLength = 0;
	p2 = s.find_first_of('\n');
	if (p2 == s.length())
	{
		return s.length();
	}
	else
	{
		while (p1 < s.length() - 1)
		{
			p2 = s.find_first_of('\n', p1 + 1);
			curLength = p2 - p1;
			if (curLength > maxLength)
			{
				maxLength = curLength;
			}
			p1 = p2;
		}
		return maxLength;
	}
}