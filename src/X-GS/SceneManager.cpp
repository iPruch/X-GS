#include <X-GS/SceneManager.hpp>
#include <cassert>

namespace xgs {
	
	SceneManager::SceneManager(sf::RenderWindow& window)
	: mWindow(window)
	, mCurrentScene()
	, mNextScene()
	, mSceneChangeRequest(false)
	{
		// Load resources here (RAII)
		
	}
	
	// Save next scene ID and request to change the scene
	void SceneManager::loadScene(Scenes::ID sceneID)
	{
		mNextScene = sceneID;
		mSceneChangeRequest = true;
	}
	
	Scene::ScenePtr SceneManager::createScene(Scenes::ID sceneID)
	{
		auto found = mFactories.find(sceneID);
		assert(found != mFactories.end());
		
		return found->second();
	}
	
	// Change the scene when it is safe
	void SceneManager::switchScene()
	{
		mCurrentScene.reset();
		mCurrentScene = std::move(createScene(mNextScene));
		mSceneChangeRequest = false;
	}
	
	void SceneManager::update(const HiResDuration &dt)
	{
		// If a scene change is requested, don't update (for safety)
		if (!mSceneChangeRequest)
			mCurrentScene->update(dt);
		
		// Perform the scene change when requested
		if (mSceneChangeRequest)
			switchScene();
	}
	
	void SceneManager::render()
	{
		// If a scene change is requested, don't render (for safety)
		if (!mSceneChangeRequest)
			mCurrentScene->render();
	}
	
	void SceneManager::handleEvent(const sf::Event &event)
	{
		// If a scene change is requested, don't handle events (for safety)
		if (!mSceneChangeRequest)
			mCurrentScene->handleEvent(event);
	}
	
	SceneManager::~SceneManager()
	{
		// Cleanup
	}
}