#include "HUDgame.h"

dtn::HUDgame::HUDgame(int player_ID, sf::RenderWindow& dest)
	: HUD(dest)
{
	m_playerID = player_ID;
	m_playerMana = 0;
	m_opponentMana = 0;

	// setup labels
	m_playerManaText = std::make_shared<tgui::Label>(tgui::Label());
	m_playerManaText->setText("Your mana: 0");
	m_opponentManaText = std::make_shared<tgui::Label>(tgui::Label());
	m_opponentManaText->setText("Your opponent's mana: 0");

	// setup button
	m_endTurnButton = std::make_shared<tgui::Button>(tgui::Button());
	m_endTurnButton->setText("End Turn");
	m_endTurnButton->connect("clicked",
		std::bind(&HUDgame::onEndTurnButtonClicked, this));

	dtn::WidgetUtilities::layoutBegin();
	m_opponentManaText->setPosition(dtn::WidgetUtilities::windowLeftJustified(m_opponentManaText));
	m_endTurnButton->setPosition(dtn::WidgetUtilities::windowLeftJustified(m_endTurnButton));
	m_playerManaText->setPosition(dtn::WidgetUtilities::windowLeftJustified(m_playerManaText));
	dtn::WidgetUtilities::layoutEnd();

	m_GUI->add(m_playerManaText);
	m_GUI->add(m_opponentManaText);
	m_GUI->add(m_endTurnButton);

	// initialize mana text
	setPlayerManaText(0);
	setOpponentManaText(0);

	// setup listeners
	dtn::GlobalEventQueue::getInstance()->attachListener(dtn::Event::EventType::MANA_CHANGED,
		std::bind(&HUDgame::onManaChanged, this, std::placeholders::_1));
}

dtn::HUDgame::~HUDgame()
{
	m_GUI->removeAllWidgets();
}

void dtn::HUDgame::update(float dt)
{

}

void dtn::HUDgame::handleEvent(sf::Event e)
{
	m_GUI->handleEvent(e);
}

void dtn::HUDgame::setPlayerManaText(int amount)
{
	std::stringstream ss;
	ss << "Your mana: " << amount;
	m_playerManaText->setText(ss.str());
}

void dtn::HUDgame::setOpponentManaText(int amount)
{
	std::stringstream ss;
	ss << "Your opponent's mana: " << amount;
	m_opponentManaText->setText(ss.str());
}

void dtn::HUDgame::onManaChanged(std::shared_ptr<dtn::Event> e)
{
	EventManaChanged* cast = dynamic_cast<EventManaChanged*>(e.get());
	if (cast->playerID == m_playerID)
		setPlayerManaText(cast->newManaValue);
	else
		setOpponentManaText(cast->newManaValue);
}

void dtn::HUDgame::onEndTurnButtonClicked()
{
	dtn::GlobalEventQueue::getInstance()->pushEvent(
		std::shared_ptr<dtn::Event>(new dtn::EventEndTurn(m_playerID)));
}
