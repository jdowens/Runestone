#include "widgetutilities.h"

tgui::Widget::Ptr dtn::WidgetUtilities::m_previousWidget = NULL;
float dtn::WidgetUtilities::m_curY = 0;

void dtn::WidgetUtilities::layoutBegin()
{
	m_curY = 0;
}

sf::Vector2f dtn::WidgetUtilities::windowCentered(tgui::Widget::Ptr wgt)
{
	sf::Vector2f ret;
	ret.x = dtn::Utilities::WINDOW_WIDTH / 2 - wgt->getSize().x / 2;
	if (m_previousWidget == NULL)
	{
		ret.y = 0;
		m_previousWidget = wgt;
	}
	else
	{
		m_curY += m_previousWidget->getSize().y;
		ret.y = m_curY;
	}
	return ret;
}

sf::Vector2f dtn::WidgetUtilities::windowLeftJustified(tgui::Widget::Ptr wgt)
{
	sf::Vector2f ret;
	ret.x = 0;
	if (m_previousWidget == NULL)
	{
		ret.y = 0;
		m_previousWidget = wgt;
	}
	else
	{
		m_curY += m_previousWidget->getSize().y;
		ret.y = m_curY;
	}
	return ret;
}

sf::Vector2f dtn::WidgetUtilities::windowRightJustified(tgui::Widget::Ptr wgt)
{
	sf::Vector2f ret;
	ret.x = dtn::Utilities::WINDOW_WIDTH - wgt->getSize().x;
	if (m_previousWidget == NULL)
	{
		ret.y = 0;
		m_previousWidget = wgt;
	}
	else
	{
		m_curY += m_previousWidget->getSize().y;
		ret.y = m_curY;
	}
	return ret;
}

void dtn::WidgetUtilities::layoutEnd()
{
	m_previousWidget = NULL;
}
