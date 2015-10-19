#include "screen.h"

dtn::Screen::Screen()
{

}

void dtn::Screen::loadBackground(std::string fileName)
{
	m_backgroundTexture = std::shared_ptr<sf::Texture>(new sf::Texture);
	m_backgroundTexture->loadFromFile(fileName);
	m_background.setTexture(*m_backgroundTexture);
}

void dtn::Screen::moveBackground(sf::Vector2f newLoc)
{
	m_background.setPosition(newLoc);
}

void dtn::Screen::update(float dt)
{
	m_processManager.update(dt);
}

void dtn::Screen::render(sf::RenderWindow & window)
{
	window.draw(m_background);
}
