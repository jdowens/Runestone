#include "processmoverenderable.h"

// constructor
dtn::ProcessMoveRenderable::ProcessMoveRenderable(
	std::shared_ptr<dtn::Renderable> renderable, sf::Vector2f destination,
	float speed)
{
	m_renderable = renderable;
	m_destination = destination;
	m_direction = sf::Vector2f(0.f, 0.f);
	m_speed = speed;
	m_minimumSpeed = m_speed*0.05;
	m_curSpeed = 0.0f;
	m_repeated = false;
	m_dead = false;
	m_distanceEstimate = 0.0f;
}

// update
/*
	Called each ProcessManager update.
*/
bool dtn::ProcessMoveRenderable::update(float dt)
{
	float remDist = remainingDistance();
	if (remDist < 0.45*m_distanceEstimate)
	{
		m_curSpeed -= m_acceleration*dt;
		if (m_curSpeed < m_minimumSpeed)
			m_curSpeed = m_minimumSpeed;
	}
	else if (remDist > 0.55*m_distanceEstimate)
	{
		if (m_curSpeed < m_speed)
			m_curSpeed += m_acceleration*dt;
		if (m_curSpeed > m_speed)
			m_curSpeed = m_speed;
	}
	sf::Vector2f newPosition = m_renderable->getSprite().getPosition();
	// if renderable outside of window (strange floating point bug)
	// snap to position
	if (newPosition.x < 0 || newPosition.x > dtn::Utilities::WINDOW_WIDTH)
	{
		std::cout << "OUT OF RANGE MOVEMENT X" << '\n';
		newPosition.x = static_cast<float>(m_destination.x);
		newPosition.y = static_cast<float>(m_destination.y);
		m_dead = true;
	}
	else if (newPosition.y < 0 || newPosition.y > dtn::Utilities::WINDOW_HEIGHT)
	{
		std::cout << "OUT OF RANGE MOVEMENT Y" << '\n';
		newPosition.x = static_cast<float>(m_destination.x);
		newPosition.y = static_cast<float>(m_destination.y);
		m_dead = true;
	}
	// if delta time is huge, snap to position (to avoid tunneling)
	else if (dt >= 0.2)
	{
		std::cout << "DELTA TIME TOO GREAT IN MOVE RENDERABLE: \n";
		std::cout << m_renderable->getEntityID() << '\n';
		std::cout << dt << "\n\n";
		newPosition.x = static_cast<float>(m_destination.x);
		newPosition.y = static_cast<float>(m_destination.y);
		m_dead = true;
	}
	// if within tolerance snap to position
	else if (std::abs(newPosition.x - m_destination.x) <= 3.f &&
		std::abs(newPosition.y - m_destination.y) <= 3.f)
	{
		newPosition.x = static_cast<float>(m_destination.x);
		newPosition.y = static_cast<float>(m_destination.y);
		m_dead = true;
	}
	// else move closer to position
	else
	{
		newPosition.x += m_curSpeed * m_direction.x*dt;
		newPosition.y += m_curSpeed * m_direction.y*dt;
	}
	m_renderable->getSprite().setPosition(newPosition);
	return m_dead;
}

// onAttach
/*
	Calculate direction vector from current position of renderable at time of attach.
*/
void dtn::ProcessMoveRenderable::onAttach()
{
	sf::Vector2f renderablePos = m_renderable->getSprite().getPosition();
	float distX = m_destination.x - renderablePos.x;
	float distY = m_destination.y - renderablePos.y;
	float magnitude = std::sqrt(std::pow(distX, 2) + std::pow(distY, 2));
	float uVecX = distX / magnitude;
	float uVecY = distY / magnitude;
	m_direction = sf::Vector2f(uVecX, uVecY);
	std::cout << "MOVE STARTED: \n";
	std::cout << m_renderable->getEntityID()
		<< ' ' << m_renderable->getSprite().getPosition().x << ' ' << m_renderable->getSprite().getPosition().y 
		<< ' ' << m_destination.x << ' ' << m_destination.y << "\n\n";
	// accelerate to max speed at 50 % of distance traveled
	m_distanceEstimate = remainingDistance();
	float time = 2*(m_distanceEstimate / m_speed);
	m_acceleration = (m_speed / (time / 2));
}

// onDeath
void dtn::ProcessMoveRenderable::onDeath()
{
	std::cout << "MOVE COMPLETED:\n";
	std::cout << "\nENTITY_ID: " << m_renderable->getEntityID() << "\n\n";
}

float dtn::ProcessMoveRenderable::remainingTime()
{
	float dist = remainingDistance();
	return dist / m_speed;
}

float dtn::ProcessMoveRenderable::remainingDistance()
{
	float dist;
	if (m_renderable.get() != NULL)
		dist = dtn::Utilities::VectorDistance(m_renderable->getSprite().getPosition(), m_destination);
	else
		dist = 0;
	return dist;
}
