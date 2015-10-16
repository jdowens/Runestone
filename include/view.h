/*
	view.h
	An abstraction for a view to the game session.
*/
#ifndef _VIEW_H
#define _VIEW_H

// dtn includes
#include "player.h"

namespace dtn
{
	class View
	{
	public :
		// constructor
		View(int playerID);
	protected :
		int m_playerID;
		dtn::Player m_player;
	};
}
#endif