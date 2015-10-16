/*
	processmoverenderable.h
	A process to move a renderable using linear constant speed from point a to point b.
*/
#ifndef _PROCESSMOVERENDERABLE_H
#define _PROCESSMOVERENDERABLE_H

// c++ includes
#include<cmath>
#include<iostream>
#include<memory>

// dtn includes
#include "renderable.h"
#include "process.h"
#include "utilities.h"

namespace dtn
{
	class Runestone;

	class ProcessMoveRenderable : public Process
	{
	public:
		// constructor
		ProcessMoveRenderable(std::shared_ptr<dtn::Renderable> renderable, sf::Vector2f destination,
			float speed);

		// vitrual overrides
		virtual bool update(float dt);
		virtual void onAttach();
		virtual void onDeath();
	private:
		float m_speed;
		std::shared_ptr<dtn::Renderable> m_renderable;
		sf::Vector2f m_destination;
		sf::Vector2f m_direction;
	};
}

#endif