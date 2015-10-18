#include "playerdeck.h"

// constructor
dtn::PlayerDeck::PlayerDeck(int id)
{
	m_playerID = id;
}

// addRunestone
/*
	Take ownership of and add a runestone to the deck.
*/
void dtn::PlayerDeck::addRunestone(std::shared_ptr<dtn::Runestone> runestone)
{
	runestone->setOwner(m_playerID);
	runestone->setState(dtn::Runestone::state::IN_DECK);
	m_runestones.push_back(runestone);
}

// draw
/*
	Remove top runestone from deck and return it.
*/
std::shared_ptr<dtn::Runestone> dtn::PlayerDeck::draw()
{
	std::shared_ptr<dtn::Runestone> ret = NULL;
	if (!m_runestones.empty())
	{
		ret = m_runestones.back();
		m_runestones.pop_back();
	}
	return ret;
}

// shuffle
void dtn::PlayerDeck::shuffle()
{
	// obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(m_runestones.begin(), m_runestones.end(), std::default_random_engine(seed));
}

// size
int dtn::PlayerDeck::size()
{
	return m_runestones.size();
}

// render
void dtn::PlayerDeck::render(sf::RenderWindow& window)
{
	sf::CircleShape circle(static_cast<float>(dtn::Utilities::PIXELS_PER_TILE_X) / 2.f);
	circle.setFillColor(sf::Color::White);
	for (std::vector<std::shared_ptr<dtn::Runestone>>::iterator it = m_runestones.begin();
		it != m_runestones.end(); ++it)
	{
		circle.setPosition(dtn::Utilities::PIXELS_PER_TILE_X *
			(dtn::Utilities::BOARD_WIDTH + dtn::Utilities::BOARD_LEFT), dtn::Utilities::PIXELS_PER_TILE_Y *
			(dtn::Utilities::BOARD_HEIGHT + dtn::Utilities::BOARD_TOP));
		window.draw(circle);
	}
}


