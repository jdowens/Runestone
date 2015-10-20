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
	if (m_currentScene == NULL)
	{
		m_currentScene = scene;
		m_currentScene->onAttach(m_window);
	}
	else
	{
		m_nextScene = scene;
	}
}

void dtn::SceneManager::update(float dt)
{
	if (m_nextScene != NULL)
	{
		m_currentScene.reset();
		m_currentScene = m_nextScene;
		m_currentScene->onAttach(m_window);
		m_nextScene = NULL;
	}
	m_currentScene->update(dt, m_window);
}

void dtn::SceneManager::render()
{
	m_window.clear();
	m_currentScene->render(m_window);
	m_window.display();
}

dtn::SceneManager::SceneManager()
	: m_window(sf::VideoMode(dtn::Utilities::WINDOW_WIDTH, dtn::Utilities::WINDOW_HEIGHT, 32)
		, "Game Client", sf::Style::Default & ~sf::Style::Resize)
{

}