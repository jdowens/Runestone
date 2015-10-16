/*
	renderable.h
	A container class for all of the information of a renderable.
*/
#ifndef _RENDERABLE_H
#define _RENDERABLE_H

// c++ includes
#include<memory>
#include<string>

// sfml includes
#include<SFML/Graphics.hpp>

namespace dtn
{
	class Renderable
	{
	public :
		// constructor
		Renderable(int entityID, std::shared_ptr<sf::Texture> texture);

		// get/set
		sf::Sprite& getSprite();
		void setLos(int l);
		void setToolTip(std::string s);
		void setOwner(int o);
		int getEntityID();
		int getLos();
		std::string getToolTip();
		int getOwner();
	private :
		int m_entityID;
		int m_los;
		int m_owner;
		std::string m_tooltipData;
		std::shared_ptr<sf::Texture> m_texture;
		sf::Sprite m_sprite;
	};
}
#endif