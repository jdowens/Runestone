#include "HUDmainmenu.h"

dtn::HUDMainMenu::HUDMainMenu(sf::RenderWindow& dest)
	: HUD(dest)
{
	m_layout = std::make_shared<tgui::VerticalLayout>();
	m_ipLayout = std::make_shared<tgui::HorizontalLayout>();
	m_pNumLayout = std::make_shared<tgui::HorizontalLayout>();

	m_layout->setSize(0.25*tgui::bindWidth(*m_GUI), tgui::bindHeight(*m_GUI));

	m_ipAddressEntry = std::make_shared<tgui::EditBox>(tgui::EditBox());
	m_playerNumberEntry = std::make_shared<tgui::EditBox>(tgui::EditBox());
	m_ipLabel = std::make_shared<tgui::Label>();
	m_ipLabel->setText("IP: ");
	m_numLabel = std::make_shared<tgui::Label>();
	m_numLabel->setText("#: ");

	m_ipLayout->setSize(tgui::bindWidth(m_layout), tgui::bindHeight(m_ipAddressEntry));
	m_pNumLayout->setSize(tgui::bindWidth(m_layout), tgui::bindHeight(m_playerNumberEntry));
	m_ipLayout->add(m_ipLabel);
	m_ipLayout->add(m_ipAddressEntry);
	m_pNumLayout->add(m_numLabel);
	m_pNumLayout->add(m_playerNumberEntry);

	m_playOnlineButton = std::make_shared<tgui::Button>(tgui::Button());
	m_quitButton = std::make_shared<tgui::Button>(tgui::Button());

	m_playOnlineButton->connect("clicked", std::bind(
		&HUDMainMenu::onPlayOnlineButtonClicked, this));
	m_playOnlineButton->setText("Play Online");
	m_quitButton->connect("clicked", std::bind(
		&HUDMainMenu::onQuitButtonClicked, this));
	m_quitButton->setText("Quit");

	m_GUI->add(m_layout);
	m_layout->add(m_ipLayout);
	m_layout->add(m_pNumLayout);
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
