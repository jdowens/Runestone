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
	m_repeated = false;
	m_dead = false;
}

// update
/*
	Called each ProcessManager update.
*/
bool dtn::ProcessMoveRenderable::update(float dt)
{
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
		newPosition.x += m_speed * m_direction.x*dt;
		newPosition.y += m_speed * m_direction.y*dt;
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
}

// onDeath
void dtn::ProcessMoveRenderable::onDeath()
{
	std::cout << "MOVE COMPLETED:\n";
	std::cout << "\nENTITY_ID: " << m_renderable->getEntityID() << "\n\n";
}