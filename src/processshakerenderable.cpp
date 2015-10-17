#include "processshakerenderable.h"

dtn::ProcessShakeRenderable::ProcessShakeRenderable(std::shared_ptr<dtn::Renderable> rend, sf::Vector2f intensity, float duration)
{
	m_renderable = rend;
	m_intensity = intensity;
	m_duration = duration;
	m_curTime = 0;
	m_repeated = false;
	m_dead = false;
}

bool dtn::ProcessShakeRenderable::update(float dt)
{
	m_curTime += dt;
	if (m_curTime > m_duration)
	{
		m_dead = true;
	}
	else
	{
		float posx = dtn::Utilities::randFloat(-m_intensity.x, m_intensity.x) + m_startPosition.x;
		float posy = dtn::Utilities::randFloat(-m_intensity.y, m_intensity.y) + m_startPosition.y;
		if (m_renderable.get() != NULL)
			m_renderable->getSprite().setPosition(posx, posy);
	}
	return m_dead;
}

void dtn::ProcessShakeRenderable::onAttach()
{
	m_startPosition = m_renderable->getSprite().getPosition();
}

void dtn::ProcessShakeRenderable::onDeath()
{
	if (m_renderable.get() != NULL)
		m_renderable->getSprite().setPosition(m_startPosition);
}
