#ifndef _PROCESS_SHAKE_RENDERABLE
#define _PROCESS_SHAKE_RENDERABLE

#include <SFML/System.hpp>
#include "process.h"
#include "renderable.h"
#include "utilities.h"

namespace dtn
{
	class ProcessShakeRenderable : public Process
	{
	public :
		ProcessShakeRenderable(std::shared_ptr<dtn::Renderable> rend,
			sf::Vector2f intensity, float duration);

		// overrides
		virtual bool update(float dt);
		virtual void onAttach();
		virtual void onDeath();
	private :
		float m_duration;
		float m_curTime;
		sf::Vector2f m_intensity;
		sf::Vector2f m_startPosition;
		std::shared_ptr<dtn::Renderable> m_renderable;
	};
}

#endif