#include "HUD.h"

dtn::HUD::HUD(int player_ID)
{
	m_playerID = player_ID;
	m_playerMana = 0;
	m_opponentMana = 0;
	m_window = sfg::Window::Create();
	m_playerManaText = sfg::Label::Create();
	m_opponentManaText = sfg::Label::Create();
	m_window->Add(m_opponentManaText);
	m_window->Add(m_playerManaText);
}

void dtn::HUD::update(float dt)
{
	m_window->Update(dt);
}

void dtn::HUD::render(sf::RenderWindow & dest)
{
	sfgui.Display(dest);
}

void dtn::HUD::handleEvent(sf::Event e)
{
	m_window->HandleEvent(e);
}

void dtn::HUD::setPlayerManaText(int amount)
{
	std::stringstream ss;
	ss << "Your mana: " << amount;
	m_playerManaText->SetText(ss.str());
}

void dtn::HUD::setOpponentManaText(int amount)
{
	std::stringstream ss;
	ss << "Your opponent's mana: " << amount;
	m_opponentManaText->SetText(ss.str());
}
