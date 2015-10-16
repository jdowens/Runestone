/*
	renderablefactory.h
	A class for constructing renderables (holds all textures, loads them upon construction).

	Singleton class.
*/
#ifndef _RENDERABLEFACTORY_H
#define _RENDERABLEFACTORY_H

// c++ includes
#include<fstream>
#include<iostream>
#include<sstream>
#include<memory>
#include<vector>
#include<map>

// sfml includes
#include<SFML/Graphics.hpp>

// dtn includes
#include "renderable.h"

namespace dtn
{
	class RenderableFactory
	{
	public:
		// singleton getInstance
		static std::shared_ptr<RenderableFactory> getInstance();

		// renderable functions
		std::shared_ptr<dtn::Renderable> newRenderable(int textureID, int entityID);
	private :
		RenderableFactory(std::string fileName);					// private constructor
		static std::shared_ptr<dtn::RenderableFactory> m_instance;
		std::map<int, std::shared_ptr<sf::Texture>> m_textures;
	};
}

#endif