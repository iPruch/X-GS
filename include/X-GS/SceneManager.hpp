#ifndef XGS_SCENEMANAGER_HPP
#define XGS_SCENEMANAGER_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <X-GS/Time.hpp>
#include <X-GS/Scene.hpp>
#include <X-GS/Entity.hpp>
//#include <X-GS/Scenes/ScenesIdentifiers.hpp>

#include <map>

#include "ScenesIdentifiers.hpp"

namespace xgs {
    
    class SceneManager : private sf::NonCopyable
    {
		// Methods
	public:
		explicit				SceneManager(sf::RenderWindow& window);
		~SceneManager();
		
		template <typename T>
		void					registerScene(Scenes::ID stateID);
		void					loadScene(Scenes::ID sceneID);
		
		void                    update(const HiResDuration& dt);
		void                    render();
		void					handleEvent(const sf::Event& event);
        
	private:
		Scene::ScenePtr			createScene(Scenes::ID sceneID);
		void					switchScene();
		
		// Variables (member / properties)
	private:
		sf::RenderWindow&		mWindow;
		Scene::ScenePtr			mCurrentScene;
		Scenes::ID				mNextScene;
		bool					mSceneChangeRequest;
		
		std::map<Scenes::ID, std::function<Scene::ScenePtr()>>	mFactories;
    };
	
	// Template implementation
	template <typename T>
	void SceneManager::registerScene(Scenes::ID sceneID)
	{
		mFactories[sceneID] = [this] ()
		{
			return Scene::ScenePtr(new T(mWindow, *this));
		};
	}
    
} // namespace xgs

#endif // XGS_SCENEMANAGER_HPP
