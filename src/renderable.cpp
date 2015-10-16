#include "renderable.h"

// constructor
dtn::Renderable::Renderable(int entityID, std::shared_ptr<sf::Texture> texture)
{
	m_entityID = entityID;
	m_texture = texture;
	m_sprite.setTexture(*texture);
	m_los = 0;
	m_owner = 0;
	m_tooltipData = "";
}

// setLos
void dtn::Renderable::setLos(int l)
{
	m_los = l;
}

// setToolTip
void dtn::Renderable::setToolTip(std::string s)
{
	m_tooltipData = s;
}

// setOwner
void dtn::Renderable::setOwner(int o)
{
	m_owner = o;
}

// getSprite
sf::Sprite& dtn::Renderable::getSprite()
{
	return m_sprite;
}

// getEntityID
int dtn::Renderable::getEntityID()
{
	return m_entityID;
}

// getLos
int dtn::Renderable::getLos()
{
	return m_los;
}

// getToolTip
std::string dtn::Renderable::getToolTip()
{
	return m_tooltipData;
}

// getOwner
int dtn::Renderable::getOwner()
{
	return m_owner;
}