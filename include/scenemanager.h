#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include<SFML/Graphics.hpp>
#include<memory>
#include "scene.h"

namespace dtn
{
	class SceneManager
	{
	public :
		static std::shared_ptr<dtn::SceneManager> getInstance();
		void runScene(std::shared_ptr<Scene> scene);
		void update(float dt, sf::RenderWindow& window);
		void render(sf::RenderWindow& window);
	private :
		SceneManager();
		std::shared_ptr<Scene> m_currentScene;
		static std::shared_ptr<dtn::SceneManager> m_instance;
	};
}

#endif