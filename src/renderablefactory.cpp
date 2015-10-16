#include "renderablefactory.h"

// set instance to NULL
std::shared_ptr<dtn::RenderableFactory> dtn::RenderableFactory::m_instance = NULL;

// getInstance
/*
	Returns the global intialization of the class. Creates a new one if it does not exist.
*/
std::shared_ptr<dtn::RenderableFactory> dtn::RenderableFactory::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = std::shared_ptr<dtn::RenderableFactory>(new dtn::RenderableFactory("Resources/renderabledatabase.csv"));
	}
	return m_instance;
}

// newRenderable
/*
	Creates a new renderable given a textureID and entityID.
*/
std::shared_ptr<dtn::Renderable> dtn::RenderableFactory::newRenderable(int textureID, int entityID)
{
	std::shared_ptr<dtn::Renderable> ret =
		std::shared_ptr<dtn::Renderable>(new dtn::Renderable(entityID,
		m_textures[textureID]));
	return ret;
}

// constructor
/*
	Loads all textures to memory using config file.
*/
dtn::RenderableFactory::RenderableFactory(std::string fileName)
{
	std::ifstream file(fileName.c_str());
	if (!file)
	{
		std::cout << "FAILED TO OPEN RENDERABLEDATABASE.CSV IN RENDERABLE FACTORY..." << std::endl;
	}

	file.ignore(256, '\n');
	std::string line;
	while (file)
	{
		std::getline(file, line, '\n');
		if (line == "")
			break;
		std::stringstream ss(line);
		std::string token;
		std::vector<std::string> vecLine;
		while (std::getline(ss, token, ','))
			vecLine.push_back(token);
		std::shared_ptr<sf::Texture> temp(new sf::Texture());
		temp->loadFromFile(vecLine[1]);
		m_textures[std::atoi(vecLine[0].c_str())] = temp;
	}
}