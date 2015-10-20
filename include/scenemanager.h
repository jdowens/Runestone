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
		void update(float dt);
		void render();
	private :
		SceneManager();
		sf::RenderWindow m_window;
		std::shared_ptr<Scene> m_currentScene;
		std::shared_ptr<Scene> m_nextScene;
		static std::shared_ptr<dtn::SceneManager> m_instance;
	};
}

#endif