/*
	event.h
	This file contains the definitions of all of the types of events used in the game's event based
	messaging system.
*/

#ifndef _EVENT_H
#define _EVENT_H

// c++ includes
#include<sstream>
#include<string>

// SFML includes
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

// dtn includes
#include "runestone.h"

namespace dtn
{
	class Event
	{
	public :
		// enum EventType
		typedef enum class EventType : unsigned char
		{
			UNKNOWN = 0x00,
			GAME_QUIT = 0x01,
			END_TURN = 0x02,
			RUNESTONE_PLAY = 0x03,
			RUNESTONE_MOVE = 0x04,
			RUNESTONE_DRAW = 0x05,
			RUNESTONE_ATTACK = 0x06,
			CLICK_AND_DRAG = 0x07,
			SINGLE_CLICK = 0x08,
			MOUSE_HOVERED = 0x09,
			ADD_RENDERABLE = 0x0A,
			MOVE_RENDERABLE = 0x0B,
			DELETE_RENDERABLE = 0x0C,
			UPDATE_RENDERABLE_LOS = 0x0D,
			UPDATE_RENDERABLE_TOOLTIP = 0x0E,
			UPDATE_RENDERABLE_OWNER = 0x0F,
			ENTITY_ADDED = 0x10,
			ENTITY_MOVED = 0x11,
			ENTITY_BATTLE = 0x12,
			ENTITY_DRAWN = 0x13,
			MANA_CHANGED = 0x14,
			ENTITY_MOVE_FLAG_CHANGED = 0x15,
			REQUEST_ENTITY_MOVE_DECAL = 0x16,
			RECEIVED_ENTITY_MOVE_DECAL = 0x17,
			RECEIVED_BOARD_LOS_DECAL = 0x18,
			ALL_EVENTS = 0xFE
			// REMEBER UPDATE STEPS 1 2 3 4 (step 4 in eventmanager.cpp)
		};
		
		// constructor
		Event(EventType type);

		// virtual overrides
		virtual std::string toString() = 0;

		// static functions
		// have to update all 3 of these when adding new event types
		static std::shared_ptr<dtn::Event> stringToEvent(std::string str);
		static EventType stringToEventType(std::string);
		static std::string eventTypeToString(EventType type);

		// get/set
		EventType getType();	
	protected :
		EventType m_type;
	};

	// EventGameQuit
	// signals a player quit the game
	struct EventGameQuit : public Event
	{
		EventGameQuit();
		virtual std::string toString();
	};

	// EventEndTurn
	// signals playerID attempted to end their turn
	struct EventEndTurn : public Event
	{
		EventEndTurn(int playerID);
		int playerID;
		virtual std::string toString();
	};

	// EventRunestonePlay
	// signals a player tried to play a runestone
	struct EventRunestonePlay : public Event
	{
		EventRunestonePlay(int entityID, sf::Vector2i dest);
		virtual std::string toString();
		int entityID;
		sf::Vector2i dest;
	};

	// EventRunestoneMove
	// signals a player tried to move a runestone
	struct EventRunestoneMove : public Event
	{
		EventRunestoneMove(sf::Vector2i source, sf::Vector2i dest);
		virtual std::string toString();
		sf::Vector2i source;
		sf::Vector2i dest;
	};

	// EventRunestoneDraw
	// signals a player tried to draw a runestone
	struct EventRunestoneDraw : public Event
	{
		EventRunestoneDraw(int playerID);
		virtual std::string toString();
		int playerID;
	};

	// EventRunestoneAttack
	// signals a player tried to attack with a runestone
	struct EventRunestoneAttack : public Event
	{
		EventRunestoneAttack(sf::Vector2i source, sf::Vector2i dest);
		virtual std::string toString();
		sf::Vector2i source;
		sf::Vector2i dest;
	};

	// EventClickAndDrag
	// signals a click and drag event occured
	struct EventClickAndDrag : public Event
	{
		EventClickAndDrag(sf::Vector2i s, sf::Vector2i d, sf::Mouse::Button b);
		virtual std::string toString();
		sf::Vector2i source;
		sf::Vector2i dest;
		sf::Mouse::Button button;
	};

	// EventSingleClick
	// signals a single click event occured
	struct EventSingleClick : public Event
	{
		EventSingleClick(sf::Vector2i p, sf::Mouse::Button b);
		virtual std::string toString();
		sf::Vector2i pos;
		sf::Mouse::Button button;
	};

	// EventMouseHovered
	// signals the mouse is hovering over entID
	struct EventMouseHovered : public Event
	{
		EventMouseHovered(int entID);
		virtual std::string toString();
		int entityID;
	};

	// EventAddRenderable
	// signals a new renderable has come into view (GameScreen needs to add the renderable)
	struct EventAddRenderable : public Event
	{
		EventAddRenderable(sf::Vector2i p, int entID, int rendID);
		virtual std::string toString();
		sf::Vector2i pos;
		int entityID;
		int renderableID;
	};

	// EventMoveRenderable
	// signals a renderable needs to move
	struct EventMoveRenderable : public Event
	{
		EventMoveRenderable(int entID, sf::Vector2i d, float v);
		virtual std::string toString();
		int entityID;
		sf::Vector2i dest;
		float velocity;
	};

	// EventDeleteRenderable
	// signals a renderable needs to be deleted
	struct EventDeleteRenderable : public Event
	{
		EventDeleteRenderable(int entID);
		virtual std::string toString();
		int entityID;
	};

	// EventUpdateRenderableLos
	// signals the LOS on a renderable needs to change
	struct EventUpdateRenderableLos : public Event
	{
		EventUpdateRenderableLos(int entID, int l);
		virtual std::string toString();
		int entityID;
		int los;
	};

	// EventUpdateRenderableTooltip
	// signals a renderable's tooltip needs to change
	struct EventUpdateRenderableTooltip : public Event
	{
		EventUpdateRenderableTooltip(int entID, std::string s);
		virtual std::string toString();
		int entityID;
		std::string tooltip;
	};

	// EventUpdateRenderableOwner
	// signals a renderable's owner needs to change
	struct EventUpdateRenderableOwner : public Event
	{
		EventUpdateRenderableOwner(int entID, int o);
		virtual std::string toString();
		int entityID;
		int owner;
	};

	// EventEntityAdded
	// signals an entity has been added to battlefield on server side
	struct EventEntityAdded : public Event
	{
		EventEntityAdded(int entID, int o, int l, std::string s, sf::IntRect b, int rendID);
		virtual std::string toString();
		int entityID;
		int owner;
		int los;
		std::string tooltip;
		sf::IntRect bounds;
		int renderableID;
	};

	// EventEntityMoved
	// signals an entity has moved
	struct EventEntityMoved : public Event
	{
		EventEntityMoved(int entID, sf::Vector2i d, std::string s);
		virtual std::string toString();
		int entityID;
		sf::Vector2i dest;
		std::string tooltip;
	};

	// EventEntityBattle
	// signals entities have conducted battle
	struct EventEntityBattle : public Event
	{
		EventEntityBattle(int entID1, int entID2, std::string s1, std::string s2,
			bool ad, bool dd);
		virtual std::string toString();
		int attackerEntityID;
		int defenderEntityID;
		std::string tooltipAttacker;
		std::string tooltipDefender;
		bool attackerDead;
		bool defenderDead;
	};

	// EventEntityDrawn
	// signals an entity has been drawn
	struct EventEntityDrawn : public Event
	{
		EventEntityDrawn(int entID, int o, int l, std::string s, sf::Vector2i sour, sf::Vector2i d, int rendID);
		virtual std::string toString();
		int entityID;
		int owner;
		int los;
		std::string tooltip;
		sf::Vector2i source;
		sf::Vector2i dest;
		int renderableID;
	};

	//EventManaChanged
	// signals that a player's mana has changed
	struct EventManaChanged : public Event
	{
		EventManaChanged(int pID, int newMana);
		virtual std::string toString();
		int playerID;
		int newManaValue;
	};

	// EventEntityMoveFlagChanged
	/*
	// signals that an entity's move flag has changed
	*/
	struct EventEntityMoveFlagChanged : public Event
	{
		EventEntityMoveFlagChanged(int entID, bool f);
		virtual std::string toString();
		int entityID;
		bool flag;
	};

	// EventRequestEntityMoveDecal
	/*
	// ask the server for the movement decal for the hovered runestone
	*/
	struct EventRequestEntityMoveDecal : public Event
	{
		EventRequestEntityMoveDecal(int pID, sf::Vector2i src);
		virtual std::string toString();
		int playerID;
		sf::Vector2i source;
	};

	// EventReceivedEntityMoveDecal
	/*
	// Contains the requested movement decal from the server
	*/
	struct EventReceivedEntityMoveDecal : public Event
	{
		EventReceivedEntityMoveDecal(std::vector<sf::Vector2i>& locs);
		virtual std::string toString();
		std::vector<sf::Vector2i> movementLocations;
	};

	// EventReceivedBoardLOSDecal
	/*
		Received the LOS decal from the server.
	*/
	struct EventReceivedBoardLOSDecal : public Event
	{
		EventReceivedBoardLOSDecal(std::vector<sf::Vector2i>& locs);
		virtual std::string toString();
		std::vector<sf::Vector2i> locations;
	};

}

#endif