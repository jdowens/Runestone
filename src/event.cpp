#include "event.h"

// constructor
dtn::Event::Event(dtn::Event::EventType type)
{
	m_type = type;
}

// getType
dtn::Event::EventType dtn::Event::getType()
{
	return m_type;
}

// HAVE TO UPDATE THIS [1]
std::string dtn::Event::eventTypeToString(dtn::Event::EventType type)
{
	std::string ret = "";
	switch (type)
	{
	case dtn::Event::EventType::GAME_QUIT: ret = "GAME_QUIT"; break;
	case dtn::Event::EventType::END_TURN: ret = "END_TURN"; break;
	case dtn::Event::EventType::RUNESTONE_PLAY: ret = "RUNESTONE_PLAY"; break;
	case dtn::Event::EventType::RUNESTONE_MOVE: ret = "RUNESTONE_MOVE"; break;
	case dtn::Event::EventType::RUNESTONE_DRAW: ret = "RUNESTONE_DRAW"; break;
	case dtn::Event::EventType::RUNESTONE_ATTACK: ret = "RUNESTONE_ATTACK"; break;
	case dtn::Event::EventType::CLICK_AND_DRAG : ret = "CLICK_AND_DRAG"; break;
	case dtn::Event::EventType::SINGLE_CLICK: ret = "SINGLE_CLICK"; break;
	case dtn::Event::EventType::MOUSE_HOVERED: ret = "MOUSE_HOVERED"; break;
	case dtn::Event::EventType::ADD_RENDERABLE: ret = "ADD_RENDERABLE"; break;
	case dtn::Event::EventType::MOVE_RENDERABLE: ret = "MOVE_RENDERABLE"; break;
	case dtn::Event::EventType::DELETE_RENDERABLE: ret = "DELETE_RENDERABLE"; break;
	case dtn::Event::EventType::UPDATE_RENDERABLE_LOS: ret = "UPDATE_RENDERABLE_LOS"; break;
	case dtn::Event::EventType::UPDATE_RENDERABLE_TOOLTIP: ret = "UPDATE_RENDERABLE_TOOLTIP"; break;
	case dtn::Event::EventType::UPDATE_RENDERABLE_OWNER: ret = "UPDATE_RENDERABLE_OWNER"; break;
	case dtn::Event::EventType::ENTITY_ADDED: ret = "ENTITY_ADDED"; break;
	case dtn::Event::EventType::ENTITY_MOVED: ret = "ENTITY_MOVED"; break;
	case dtn::Event::EventType::ENTITY_BATTLE: ret = "ENTITY_BATTLE"; break;
	case dtn::Event::EventType::ENTITY_DRAWN: ret = "ENTITY_DRAWN"; break;
	case dtn::Event::EventType::MANA_CHANGED: ret = "MANA_CHANGED"; break;
	case dtn::Event::EventType::ENTITY_MOVE_FLAG_CHANGED: ret = "ENTITY_MOVE_FLAG_CHANGED"; break;
	case dtn::Event::EventType::REQUEST_ENTITY_MOVE_DECAL: ret = "REQUEST_ENTITY_MOVE_DECAL"; break;
	case dtn::Event::EventType::RECEIVED_ENTITY_MOVE_DECAL: ret = "RECEIVED_ENTITY_MOVE_DECAL"; break;
	case dtn::Event::EventType::UNKNOWN: ret = "UNKNOWN"; break;
	}
	return ret;
}

// HAVE TO UPDATE THIS [2]
/*
	Giant switch statement the handles converting strings to events (strings are received
	over serial com).
*/
std::shared_ptr<dtn::Event> dtn::Event::stringToEvent(std::string str)
{
	std::shared_ptr<dtn::Event> ret = NULL;
	std::stringstream ss(str);
	std::string word;
	ss >> word;
	ss >> word;
	dtn::Event::EventType type = stringToEventType(word);
	switch (type)
	{
	case dtn::Event::EventType::GAME_QUIT:
	{
		ret = std::shared_ptr<dtn::Event>(new EventGameQuit());
	}
		break;
	case dtn::Event::EventType::END_TURN:
	{
		int playerID; ss >> playerID;
		ret = std::shared_ptr<dtn::Event>(new EventEndTurn(playerID));
	}
		break;
	case dtn::Event::EventType::RUNESTONE_PLAY:
	{
		int dstX, dstY, entID;
		ss >> word >> entID >> word >> dstX >> dstY;
		ret = std::shared_ptr<dtn::Event>(new EventRunestonePlay(entID,
			sf::Vector2i(dstX, dstY)));
	} 
		break;
	case dtn::Event::EventType::RUNESTONE_MOVE:
	{
		int srcX, srcY, dstX, dstY;
		ss >> word >> srcX >> srcY >> word >> dstX >> dstY;
		ret = std::shared_ptr<dtn::Event>(new EventRunestoneMove(sf::Vector2i(srcX, srcY),
			sf::Vector2i(dstX, dstY)));
	}
		break;
	case dtn::Event::EventType::RUNESTONE_DRAW:
	{
		int playerID; ss >> playerID;
		ret = std::shared_ptr<dtn::Event>(new EventRunestoneDraw(playerID));
	}
		break;
	case dtn::Event::EventType::RUNESTONE_ATTACK:
	{
		int srcX, srcY, dstX, dstY;
		ss >> word >> srcX >> srcY >> word >> dstX >> dstY;
		ret = std::shared_ptr<dtn::Event>(new EventRunestoneAttack(sf::Vector2i(srcX, srcY),
			sf::Vector2i(dstX, dstY)));
	}
		break;
	case dtn::Event::EventType::CLICK_AND_DRAG:
	{
		int srcX,  srcY,  dstX,  dstY,  b;
		ss >> word >> srcX >> srcY >> word >> dstX >> dstY >> word >> b;
		ret = std::shared_ptr<dtn::Event>(new EventClickAndDrag(
			sf::Vector2i(srcX, srcY), sf::Vector2i(dstX, dstY), sf::Mouse::Button(b)));
	}
		break;
	case dtn::Event::EventType::SINGLE_CLICK:
	{
		int posX, posY, b;
		ss >> word >> posX >> posY >> word >> b;
		ret = std::shared_ptr<dtn::Event>(new EventSingleClick(
			sf::Vector2i(posX, posY), sf::Mouse::Button(b)));
	}
		break;
	case dtn::Event::EventType::MOUSE_HOVERED:
	{
		int entID;
		ss >> word >> entID;
		ret = std::shared_ptr<dtn::Event>(new EventMouseHovered(
			entID));
	}
		break;
	case dtn::Event::EventType::ADD_RENDERABLE:
	{
		int posX, posY, entID, rendID;
		ss >> word >> posX >> posY >> word >> entID >> word >> rendID;
		ret = std::shared_ptr<dtn::Event>(new EventAddRenderable(
			sf::Vector2i(posX, posY), entID, rendID));
	}
		break;
	case dtn::Event::EventType::MOVE_RENDERABLE:
	{
		int entID, destX, destY;
		float veloc;
		ss >> word >> entID >> word >> destX >> destY >> word >> veloc;
		ret = std::shared_ptr<dtn::Event>(new EventMoveRenderable(
			entID, sf::Vector2i(destX, destY), veloc));
	}
		break;
	case dtn::Event::EventType::DELETE_RENDERABLE:
	{
		int entID;
		ss >> word >> entID;
		ret = std::shared_ptr<dtn::Event>(new EventDeleteRenderable(
			entID));
	}
		break;
	case dtn::Event::EventType::UPDATE_RENDERABLE_LOS:
	{
		int entID, los;
		ss >> word >> entID >> word >> los;
		ret = std::shared_ptr<dtn::Event>(new EventUpdateRenderableLos(
			entID, los));
	}
		break;
	case dtn::Event::EventType::UPDATE_RENDERABLE_TOOLTIP:
	{
		int entID;
		std::string str;
		char junk;
		ss >> word >> entID;
		ss >> word >> junk;
		std::getline(ss, str, '\"');
		ret = std::shared_ptr<dtn::Event>(new EventUpdateRenderableTooltip(
			entID, str));
	}
		break;
	case dtn::Event::EventType::UPDATE_RENDERABLE_OWNER:
	{
		int entID, o;
		ss >> word >> entID >> word >> o;
		ret = std::shared_ptr<dtn::Event>(new EventUpdateRenderableOwner(
			entID, o));
	}
		break;
	case dtn::Event::EventType::ENTITY_ADDED:
	{
		int entID, o, los, bX, bY, bW, bH, rendID;
		std::string str;
		char junk;
		ss >> word >> entID >> word >> o >> word >> los >> word >> junk;
		std::getline(ss, str, '\"');
		ss >> word >> bX >> bY >> bW >> bH >> word >> rendID;
		ret = std::shared_ptr<dtn::Event>(new EventEntityAdded(
			entID, o, los, str, sf::IntRect(bX, bY, bW, bH), rendID));
	}
		break;
	case dtn::Event::EventType::ENTITY_MOVED:
	{
		int entID, destX, destY;
		std::string str;
		char junk;
		ss >> word >> entID >> word >> destX >> destY >> word >> junk;
		std::getline(ss, str, '\"');
		ret = std::shared_ptr<dtn::Event>(new EventEntityMoved(
			entID, sf::Vector2i(destX, destY), str));
	}
		break;
	case dtn::Event::EventType::ENTITY_BATTLE:
	{
		int entID1, entID2;
		std::string str1, str2;
		bool ad, dd;
		char junk;
		ss >> word >> entID1 >> word >> entID2 >> word >> junk;
		std::getline(ss, str1, '\"');
		ss >> word >> junk;
		std::getline(ss, str2, '\"');
		ss >> word >> ad >> word >> dd;
		ret = std::shared_ptr<dtn::Event>(new EventEntityBattle(
			entID1, entID2, str1, str2, ad, dd));
	}
		break;
	case dtn::Event::EventType::ENTITY_DRAWN:
	{
		int entID, o, los, srcX, srcY, dstX, dstY, rendID;
		std::string str;
		char junk;
		ss >> word >> entID >> word >> o >> word >> los >> word >> junk;
		std::getline(ss, str, '\"');
		ss >> word >> srcX >> srcY >> word >> dstX >> dstY >> word >> rendID;
		ret = std::shared_ptr<dtn::Event>(new EventEntityDrawn(
			entID, o, los, str, sf::Vector2i(srcX, srcY), sf::Vector2i(
			dstX, dstY), rendID));
	}
		break;
	case dtn::Event::EventType::MANA_CHANGED:
	{
		int pID, newMana;
		ss >> word >> pID >> word >> newMana;
		ret = std::shared_ptr<dtn::Event>(new EventManaChanged(pID, newMana));
	}
		break;
	case dtn::Event::EventType::ENTITY_MOVE_FLAG_CHANGED:
	{
		int entID;
		bool f;
		ss >> word >> entID >> word >> f;
		ret = std::shared_ptr<dtn::Event>(new EventEntityMoveFlagChanged(entID, f));
	}
		break;
	case dtn::Event::EventType::REQUEST_ENTITY_MOVE_DECAL:
	{
		int pID;
		sf::Vector2i src;
		ss >> word >> pID >> word >> src.x >> src.y;
		ret = std::shared_ptr<dtn::Event>(new EventRequestEntityMoveDecal(pID, src));
	}
		break;
	case dtn::Event::EventType::RECEIVED_ENTITY_MOVE_DECAL:
	{
		std::vector<sf::Vector2i> locs;
		int list_size;
		ss >> word >> list_size;
		for (int i = 0; i < list_size; i++)
		{
			sf::Vector2i tmp;
			ss >> tmp.x >> tmp.y;
			locs.push_back(tmp);
		}
		ret = std::shared_ptr<dtn::Event>(new EventReceivedEntityMoveDecal(locs));
	}
		break;
	}
	return ret;
}

// HAVE TO UPDATE THIS [3]
dtn::Event::EventType dtn::Event::stringToEventType(std::string str)
{
	dtn::Event::EventType ret = dtn::Event::EventType::UNKNOWN;
	if (str == "GAME_QUIT")
		ret = dtn::Event::EventType::GAME_QUIT;
	else if (str == "END_TURN")
		ret = dtn::Event::EventType::END_TURN;
	else if (str == "RUNESTONE_PLAY")
		ret = dtn::Event::EventType::RUNESTONE_PLAY;
	else if (str == "RUNESTONE_MOVE")
		ret = dtn::Event::EventType::RUNESTONE_MOVE;
	else if (str == "RUNESTONE_DRAW")
		ret = dtn::Event::EventType::RUNESTONE_DRAW;
	else if (str == "RUNESTONE_ATTACK")
		ret = dtn::Event::EventType::RUNESTONE_ATTACK;
	else if (str == "CLICK_AND_DRAG")
		ret = dtn::Event::EventType::CLICK_AND_DRAG;
	else if (str == "SINGLE_CLICK")
		ret = dtn::Event::EventType::SINGLE_CLICK;
	else if (str == "MOUSE_HOVERED")
		ret = dtn::Event::EventType::MOUSE_HOVERED;
	else if (str == "ADD_RENDERABLE")
		ret = dtn::Event::EventType::ADD_RENDERABLE;
	else if (str == "MOVE_RENDERABLE")
		ret = dtn::Event::EventType::MOVE_RENDERABLE;
	else if (str == "DELETE_RENDERABLE")
		ret = dtn::Event::EventType::DELETE_RENDERABLE;
	else if (str == "UPDATE_RENDERABLE_LOS")
		ret = dtn::Event::EventType::UPDATE_RENDERABLE_LOS;
	else if (str == "UPDATE_RENDERABLE_TOOLTIP")
		ret = dtn::Event::EventType::UPDATE_RENDERABLE_TOOLTIP;
	else if (str == "UPDATE_RENDERABLE_OWNER")
		ret = dtn::Event::EventType::UPDATE_RENDERABLE_OWNER;
	else if (str == "ENTITY_ADDED")
		ret = dtn::Event::EventType::ENTITY_ADDED;
	else if (str == "ENTITY_MOVED")
		ret = dtn::Event::EventType::ENTITY_MOVED;
	else if (str == "ENTITY_BATTLE")
		ret = dtn::Event::EventType::ENTITY_BATTLE;
	else if (str == "ENTITY_DRAWN")
		ret = dtn::Event::EventType::ENTITY_DRAWN;
	else if (str == "MANA_CHANGED")
		ret = dtn::Event::EventType::MANA_CHANGED;
	else if (str == "ENTITY_MOVE_FLAG_CHANGED")
		ret = dtn::Event::EventType::ENTITY_MOVE_FLAG_CHANGED;
	else if (str == "REQUEST_ENTITY_MOVE_DECAL")
		ret = dtn::Event::EventType::REQUEST_ENTITY_MOVE_DECAL;
	else if (str == "RECEIVED_ENTITY_MOVE_DECAL")
		ret = dtn::Event::EventType::RECEIVED_ENTITY_MOVE_DECAL;
	else
		ret = dtn::Event::EventType::UNKNOWN;
	return ret;
}

// Everything that follows is how to construct each event type
// and how to convert each event type to a string
dtn::EventGameQuit::EventGameQuit()
	: Event(dtn::Event::EventType::GAME_QUIT)
{

}

std::string dtn::EventGameQuit::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	return ss.str();
}

dtn::EventEndTurn::EventEndTurn(int playerID)
	: Event(dtn::Event::EventType::END_TURN), playerID(playerID)
{

}

std::string dtn::EventEndTurn::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "PLAYER_ID: " << playerID << '\n';
	return ss.str();
}


dtn::EventRunestonePlay::EventRunestonePlay(int entID, sf::Vector2i dest)
	: Event(dtn::Event::EventType::RUNESTONE_PLAY), entityID(entID), dest(dest)
{

}

std::string dtn::EventRunestonePlay::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	ss << "DESTINATION: " << dest.x << ' ' << dest.y << '\n';
	return ss.str();
}



dtn::EventRunestoneMove::EventRunestoneMove(sf::Vector2i source, sf::Vector2i dest)
	: Event(dtn::Event::EventType::RUNESTONE_MOVE), source(source), dest(dest)
{

}

std::string dtn::EventRunestoneMove::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "SOURCE: " << source.x << ' ' << source.y << '\n';
	ss << "DESTINATION: " << dest.x << ' ' << dest.y << '\n';
	return ss.str();
}



dtn::EventRunestoneDraw::EventRunestoneDraw(int playerID)
	: Event(dtn::Event::EventType::RUNESTONE_DRAW), playerID(playerID)
{

}

std::string dtn::EventRunestoneDraw::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "PLAYER_ID: " << playerID << '\n';
	return ss.str();
}

dtn::EventRunestoneAttack::EventRunestoneAttack(sf::Vector2i source, sf::Vector2i dest)
	: Event(dtn::Event::EventType::RUNESTONE_ATTACK), source(source), dest(dest)
{

}

std::string dtn::EventRunestoneAttack::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "SOURCE: " << source.x << ' ' << source.y << '\n';
	ss << "DESTINATION: " << dest.x << ' ' << dest.y << '\n';
	return ss.str();
}

// Events from Game Screen to Battlefield

dtn::EventClickAndDrag::EventClickAndDrag(sf::Vector2i s, sf::Vector2i d, sf::Mouse::Button b)
	: dtn::Event(dtn::Event::EventType::CLICK_AND_DRAG)
{
	source = s;
	dest = d;
	button = b;
}

std::string dtn::EventClickAndDrag::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "SOURCE: " << source.x << ' ' << source.y << '\n';
	ss << "DESTINATION: " << dest.x << ' ' << dest.y << '\n';
	ss << "BUTTON: " << button << '\n';
	return ss.str();
}

dtn::EventSingleClick::EventSingleClick(sf::Vector2i p, sf::Mouse::Button b)
	: dtn::Event(dtn::Event::EventType::SINGLE_CLICK)
{
	pos = p;
	button = b;
}

std::string dtn::EventSingleClick::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "POS: " << pos.x << ' ' << pos.y << '\n';
	ss << "BUTTON: " << button << '\n';
	return ss.str();
}

dtn::EventMouseHovered::EventMouseHovered(int entID)
	: dtn::Event(dtn::Event::EventType::MOUSE_HOVERED)
{
	entityID = entID;
}

std::string dtn::EventMouseHovered::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	return ss.str();
}

// Events to Game Screen
dtn::EventAddRenderable::EventAddRenderable(sf::Vector2i p, int entID, int rendID)
	: dtn::Event(dtn::Event::EventType::ADD_RENDERABLE)
{
	pos = p;
	entityID = entID;
	renderableID = rendID;
}

std::string dtn::EventAddRenderable::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "POSITION: " << pos.x << ' ' << pos.y << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	ss << "RENDERABLE_ID: " << renderableID << '\n';
	return ss.str();
}

dtn::EventMoveRenderable::EventMoveRenderable(int entID, sf::Vector2i d, float v)
	: dtn::Event(dtn::Event::EventType::MOVE_RENDERABLE)
{
	entityID = entID;
	dest = d;
	velocity = v;
}

std::string dtn::EventMoveRenderable::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	ss << "DESTINATION: " << dest.x << ' ' << dest.y << '\n';
	ss << "VELOCITY: " << velocity << '\n';
	return ss.str();
}

dtn::EventDeleteRenderable::EventDeleteRenderable(int entID)
	: dtn::Event(dtn::Event::EventType::DELETE_RENDERABLE)
{
	entityID = entID;
}

std::string dtn::EventDeleteRenderable::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	return ss.str();
}

dtn::EventUpdateRenderableLos::EventUpdateRenderableLos(int entID, int l)
	: dtn::Event(dtn::Event::EventType::UPDATE_RENDERABLE_LOS)
{
	entityID = entID;
	los = l;
}

std::string dtn::EventUpdateRenderableLos::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	ss << "LOS: " << los << '\n';
	return ss.str();
}

dtn::EventUpdateRenderableTooltip::EventUpdateRenderableTooltip(int entID, std::string s)
	: dtn::Event(dtn::Event::EventType::UPDATE_RENDERABLE_TOOLTIP)
{
	entityID = entID;
	tooltip = s;
}

std::string dtn::EventUpdateRenderableTooltip::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	ss << "TOOLTIP: \"" << tooltip << "\"\n";
	return ss.str();
}

dtn::EventUpdateRenderableOwner::EventUpdateRenderableOwner(int entID, int o)
	: dtn::Event(dtn::Event::EventType::UPDATE_RENDERABLE_OWNER)
{
	entityID = entID;
	owner = o;
}

std::string dtn::EventUpdateRenderableOwner::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	ss << "OWNER: " << owner << '\n';
	return ss.str();
}

// Events to client
dtn::EventEntityAdded::EventEntityAdded(int entID, int o, int l, std::string s, sf::IntRect b, int rendID)
	: dtn::Event(dtn::Event::EventType::ENTITY_ADDED)
{
	entityID = entID;
	owner = o;
	los = l;
	tooltip = s;
	bounds = b;
	renderableID = rendID;
}

std::string dtn::EventEntityAdded::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	ss << "OWNER: " << owner << '\n';
	ss << "LOS: " << los << '\n';
	ss << "TOOLTIP: \"" << tooltip << "\"\n";
	ss << "BOUNDS: " << bounds.left << ' ' << bounds.top << ' '
		<< bounds.width << ' ' << bounds.height << '\n';
	ss << "RENDERABLE_ID: " << renderableID << '\n';
	return ss.str();
}

dtn::EventEntityMoved::EventEntityMoved(int entID, sf::Vector2i d, std::string s)
	: dtn::Event(dtn::Event::EventType::ENTITY_MOVED)
{
	entityID = entID;
	dest = d;
	tooltip = s;
}

std::string dtn::EventEntityMoved::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	ss << "DESTINATION: " << dest.x << ' ' << dest.y << '\n';
	ss << "TOOLTIP: \"" << tooltip << "\"\n";
	return ss.str();
}

dtn::EventEntityBattle::EventEntityBattle(int entID1, int entID2, std::string s1, std::string s2,
	bool ad, bool dd)
	: dtn::Event(dtn::Event::EventType::ENTITY_BATTLE)
{
	attackerEntityID = entID1;
	defenderEntityID = entID2;
	tooltipAttacker = s1;
	tooltipDefender = s2;
	attackerDead = ad;
	defenderDead = dd;
}

std::string dtn::EventEntityBattle::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ATTACKER: " << attackerEntityID << '\n';
	ss << "DEFENDER: " << defenderEntityID << '\n';
	ss << "TOOLTIP_ATTACKER: \"" << tooltipAttacker << "\"\n";
	ss << "TOOLTIP_DEFENDER: \"" << tooltipDefender << "\"\n";
	ss << "ATTACKER_DEAD: " << attackerDead << '\n';
	ss << "DEFENDER_DEAD: " << defenderDead << '\n';
	return ss.str();
}

dtn::EventEntityDrawn::EventEntityDrawn(int entID, int o, int l, std::string s, sf::Vector2i sour, 
	sf::Vector2i d, int rendID)
	: dtn::Event(dtn::Event::EventType::ENTITY_DRAWN)
{
	entityID = entID;
	owner = o;
	los = l;
	tooltip = s;
	source = sour;
	dest = d;
	renderableID = rendID;
}

std::string dtn::EventEntityDrawn::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	ss << "OWNER: " << owner << '\n';
	ss << "LOS: " << los << '\n';
	ss << "TOOLTIP: \"" << tooltip << "\"\n";
	ss << "SOURCE: " << source.x << ' ' << source.y << '\n';
	ss << "POSITION: " << dest.x << ' ' << dest.y << '\n';
	ss << "RENDERABLE_ID: " << renderableID << '\n';
	return ss.str();
}

dtn::EventManaChanged::EventManaChanged(int pID, int newMana)
	: dtn::Event(dtn::Event::EventType::MANA_CHANGED)
{
	playerID = pID;
	newManaValue = newMana;
}

std::string dtn::EventManaChanged::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "PLAYER_ID: " << playerID << '\n';
	ss << "NEW_MANA_VALUE: " << newManaValue << '\n';
	return ss.str();
}

dtn::EventEntityMoveFlagChanged::EventEntityMoveFlagChanged(int entID, bool f)
	: dtn::Event(dtn::Event::EventType::ENTITY_MOVE_FLAG_CHANGED)
{
	entityID = entID;
	flag = f;
}

std::string dtn::EventEntityMoveFlagChanged::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "ENTITY_ID: " << entityID << '\n';
	ss << "FLAG: " << flag << '\n';
	return ss.str();
}

dtn::EventRequestEntityMoveDecal::EventRequestEntityMoveDecal(int pID, sf::Vector2i src)
	: dtn::Event(dtn::Event::EventType::REQUEST_ENTITY_MOVE_DECAL)
{
	playerID = pID;
	source = src;
}

std::string dtn::EventRequestEntityMoveDecal::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "PLAYER_ID: " << playerID << '\n';
	ss << "SOURCE: " << source.x << ' ' << source.y << '\n';
	return ss.str();
}

dtn::EventReceivedEntityMoveDecal::EventReceivedEntityMoveDecal(std::vector<sf::Vector2i>& locs)
	: dtn::Event(dtn::Event::EventType::RECEIVED_ENTITY_MOVE_DECAL)
{
	for (auto it = locs.begin(); it != locs.end(); ++it)
	{
		movementLocations.push_back(*it);
	}
}

std::string dtn::EventReceivedEntityMoveDecal::toString()
{
	std::stringstream ss;
	ss << "EVENT_TYPE: " << eventTypeToString(m_type) << '\n';
	ss << "LIST_SIZE: " << movementLocations.size();
	for (auto it = movementLocations.begin(); it != movementLocations.end(); ++it)
	{
		ss << '\n' <<  it->x << ' ' << it->y;
	}
	ss << '\n';
	return ss.str();
}
