#include "HUD.h"

dtn::HUD::HUD(int player_ID)
{
	m_playerID = player_ID;
	m_playerMana = 0;
	m_opponentMana = 0;
	m_window = sfg::Window::Create();
	m_guiLayout = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	m_playerManaText = sfg::Label::Create();
	m_opponentManaText = sfg::Label::Create();
	m_guiLayout->Pack(m_opponentManaText);
	m_guiLayout->Pack(m_playerManaText);
	m_window->Add(m_guiLayout);
	m_window->SetPosition(sf::Vector2f((dtn::Utilities::BOARD_LEFT + dtn::Utilities::BOARD_WIDTH)*
		dtn::Utilities::PIXELS_PER_TILE_X, 0.0f));
	m_window->SetRequisition(sf::Vector2f(dtn::Utilities::BOARD_LEFT*dtn::Utilities::PIXELS_PER_TILE_X,
		(dtn::Utilities::BOARD_TOP * 2 + dtn::Utilities::BOARD_HEIGHT)*dtn::Utilities::PIXELS_PER_TILE_Y));
	m_window->SetStyle(m_window->GetStyle() & ~sfg::Window::Style::RESIZE);
	setPlayerManaText(0);
	setOpponentManaText(0);
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
