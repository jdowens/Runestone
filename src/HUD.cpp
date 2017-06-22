#include "HUD.h"

std::shared_ptr<tgui::Gui> dtn::HUD::m_GUI = NULL;

dtn::HUD::HUD(sf::RenderWindow& dest)
{
	if (m_GUI == NULL)
	{
		m_GUI = std::shared_ptr<tgui::Gui>(new tgui::Gui(dest));
		//m_GUI->setFont("Resources/source-code-pro/SourceCodePro-Black.otf");
		m_GUI->setFont("Resources/cabin/Cabin-Regular.ttf");
	}
}

void dtn::HUD::render(sf::RenderWindow & dest)
{
	m_GUI->draw();
}
