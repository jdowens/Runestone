#include "scenemanager.h"

std::shared_ptr<dtn::SceneManager> dtn::SceneManager::m_instance = NULL;

std::shared_ptr<dtn::SceneManager> dtn::SceneManager::getInstance()
{
	if (m_instance == NULL)
		m_instance = std::shared_ptr<dtn::SceneManager>(new dtn::SceneManager());
	return m_instance;
}

void dtn::SceneManager::runScene(std::shared_ptr<Scene> scene)
{
	if (m_currentScene != NULL)
		m_currentScene.reset();
	m_currentScene = scene;
	m_currentScene->onAttach();
}

void dtn::SceneManager::update(float dt, sf::RenderWindow & window)
{
	m_currentScene->update(dt, window);
}

void dtn::SceneManager::render(sf::RenderWindow & window)
{
	m_currentScene->render(window);
}

dtn::SceneManager::SceneManager()
{

}