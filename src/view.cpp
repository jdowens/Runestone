#include "view.h"

// constructor
/*
	Sets up the view with owner playerID.
*/
dtn::View::View(int playerID) : m_player(playerID)
{
	m_playerID = playerID;
}