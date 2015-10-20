#include "HUDmainmenu.h"

dtn::HUDMainMenu::HUDMainMenu(sf::RenderWindow& dest)
	: HUD(dest)
{
	m_ipAddressEntry = std::make_shared<tgui::EditBox>(tgui::EditBox());
	m_playerNumberEntry = std::make_shared<tgui::EditBox>(tgui::EditBox());
	m_playOnlineButton = std::make_shared<tgui::Button>(tgui::Button());
	m_quitButton = std::make_shared<tgui::Button>(tgui::Button());

	dtn::WidgetUtilities::layoutBegin();
	m_ipAddressEntry->setPosition(dtn::WidgetUtilities::windowCentered(m_ipAddressEntry));
	m_playerNumberEntry->setPosition(dtn::WidgetUtilities::windowCentered(m_playerNumberEntry));
	m_playOnlineButton->setPosition(dtn::WidgetUtilities::windowCentered(m_playOnlineButton));
	m_quitButton->setPosition(dtn::WidgetUtilities::windowCentered(m_quitButton));
	dtn::WidgetUtilities::layoutEnd();

	m_playOnlineButton->connect("clicked", std::bind(
		&HUDMainMenu::onPlayOnlineButtonClicked, this));
	m_quitButton->connect("clicked", std::bind(
		&HUDMainMenu::onQuitButtonClicked, this));

	m_GUI->add(m_ipAddressEntry);
	m_GUI->add(m_playerNumberEntry);
	m_GUI->add(m_playOnlineButton);
	m_GUI->add(m_quitButton);
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
