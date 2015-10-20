#ifndef _WIDGET_UTILITIES_H
#define _WIDGET_UTILITIES_H

#include "utilities.h"
#include<SFML/System.hpp>
#include<TGUI/TGUI.hpp>

namespace dtn
{
	class WidgetUtilities
	{
	public :
		static void layoutBegin();
		static sf::Vector2f windowCentered(tgui::Widget::Ptr wgt);
		static sf::Vector2f windowLeftJustified(tgui::Widget::Ptr wgt);
		static sf::Vector2f windowRightJustified(tgui::Widget::Ptr wgt);
		static void layoutEnd();
	private :
		static tgui::Widget::Ptr m_previousWidget;
		static float m_curY;
	};
}

#endif