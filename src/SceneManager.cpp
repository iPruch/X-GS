#include <X-GS/SceneManager.hpp>
#include <cassert>

namespace xgs {
	
	SceneManager::SceneManager(sf::RenderWindow& window)
	: mWindow(window)
	, currentScene()
	{
		// Load resources here (RAII)
	}
	
	void SceneManager::loadScene(Scenes::ID sceneID)
	{
		currentScene.reset();
		currentScene = std::move(createScene(sceneID));
	}
	
	Scene::ScenePtr SceneManager::createScene(Scenes::ID sceneID)
	{
		auto found = mFactories.find(sceneID);
		assert(found != mFactories.end());
		
		return found->second();
	}
	
	void SceneManager::update(const HiResDuration &dt)
	{
		currentScene->update(dt);
	}
	
	void SceneManager::render()
	{
		currentScene->render();
	}
	
	SceneManager::~SceneManager()
	{
		// Cleanup
	}
}