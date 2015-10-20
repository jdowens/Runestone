#include "HUDmainmenu.h"

dtn::HUDMainMenu::HUDMainMenu(sf::RenderWindow& dest)
	: HUD(dest)
{
	m_layout = std::make_shared<tgui::VerticalLayout>();

	m_layout->setSize(0.25*tgui::bindWidth(*m_GUI), tgui::bindHeight(*m_GUI));

	m_ipAddressEntry = std::make_shared<tgui::EditBox>(tgui::EditBox());
	m_ipAddressEntry->setDefaultText("IP Address");
	m_playerNumberEntry = std::make_shared<tgui::EditBox>(tgui::EditBox());
	m_playerNumberEntry->setDefaultText("Player Number");

	m_playOnlineButton = std::make_shared<tgui::Button>(tgui::Button());
	m_quitButton = std::make_shared<tgui::Button>(tgui::Button());

	m_playOnlineButton->connect("clicked", std::bind(
		&HUDMainMenu::onPlayOnlineButtonClicked, this));
	m_playOnlineButton->setText("Play Online");
	m_quitButton->connect("clicked", std::bind(
		&HUDMainMenu::onQuitButtonClicked, this));
	m_quitButton->setText("Quit");

	m_GUI->add(m_layout);
	m_layout->add(m_ipAddressEntry);
	m_layout->add(m_playerNumberEntry);
	m_layout->add(m_playOnlineButton);
	m_layout->add(m_quitButton);
	m_layout->insertSpace(2, 20.0F);
}

dtn::HUDMainMenu::~HUDMainMenu()
{
	m_GUI->removeAllWidgets();
}

void dtn::HUDMainMenu::update(float dt)
{

}

void dtn::HUDMainMenu::handleEvent(sf::Event e)
{
	m_GUI->handleEvent(e);
}

void dtn::HUDMainMenu::onPlayOnlineButtonClicked()
{
	std::cout << "Play clicked!\n";
	std::shared_ptr<dtn::GameClient> gc;
	gc = std::shared_ptr<dtn::GameClient>(new GameClient(
		std::atoi(m_playerNumberEntry->getText().toAnsiString().c_str()), 
		m_ipAddressEntry->getText().toAnsiString()));
	dtn::SceneManager::getInstance()->runScene(gc);
}

void dtn::HUDMainMenu::onQuitButtonClicked()
{
	std::cout << "Quit clicked!\n";
}
