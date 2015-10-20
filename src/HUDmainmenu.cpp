#include "HUDmainmenu.h"

dtn::HUDMainMenu::HUDMainMenu()
{
	m_window = sfg::Window::Create();
	m_guiLayout = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	m_ipEntry = sfg::Entry::Create("ip");
	m_playerNumberEntry = sfg::Entry::Create("pnum");
	m_playOnlineButton = sfg::Button::Create("Play Online");
	m_quitButton = sfg::Button::Create("Exit");
	m_guiLayout->Pack(m_ipEntry);
	m_guiLayout->Pack(m_playerNumberEntry);
	m_guiLayout->Pack(m_playOnlineButton);
	m_guiLayout->Pack(m_quitButton);
	m_window->Add(m_guiLayout);

	m_window->SetPosition(sf::Vector2f((dtn::Utilities::BOARD_LEFT + dtn::Utilities::BOARD_WIDTH)*
		dtn::Utilities::PIXELS_PER_TILE_X, 0.0f));
	m_window->SetRequisition(sf::Vector2f(dtn::Utilities::BOARD_LEFT*dtn::Utilities::PIXELS_PER_TILE_X,
		(dtn::Utilities::BOARD_TOP * 2 + dtn::Utilities::BOARD_HEIGHT)*dtn::Utilities::PIXELS_PER_TILE_Y));
	m_window->SetStyle(m_window->GetStyle() & ~sfg::Window::Style::RESIZE);

	m_playOnlineButton->GetSignal(sfg::Button::OnLeftClick).Connect(
		std::bind(&HUDMainMenu::onPlayOnlineButtonClicked, this));
	m_quitButton->GetSignal(sfg::Button::OnLeftClick).Connect(
		std::bind(&HUDMainMenu::onQuitButtonClicked, this));

	m_desktop.Add(m_window);

	m_stupidRectThatHasToBeDrawn.setFillColor(sf::Color::Black);
}

dtn::HUDMainMenu::~HUDMainMenu()
{
	m_desktop.RemoveAll();
}

void dtn::HUDMainMenu::update(float dt)
{
	m_desktop.Update(dt);
}

void dtn::HUDMainMenu::render(sf::RenderWindow & dest)
{
	dest.draw(m_stupidRectThatHasToBeDrawn);
	sfg::Renderer::Get().Display(dest);
}

void dtn::HUDMainMenu::handleEvent(sf::Event e)
{
	m_desktop.HandleEvent(e);
}

void dtn::HUDMainMenu::onPlayOnlineButtonClicked()
{
	dtn::SceneManager::getInstance()->runScene(
		std::shared_ptr<GameClient>(new GameClient(std::atoi(
			m_playerNumberEntry->GetText().toAnsiString().c_str()), 
			m_ipEntry->GetText().toAnsiString())));
}

void dtn::HUDMainMenu::onQuitButtonClicked()
{

}
