#ifndef XGS_SCENEMANAGER_HPP
#define XGS_SCENEMANAGER_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <X-GS/Time.hpp>
#include <X-GS/Scene.hpp>
#include <X-GS/Scenes/ScenesIdentifiers.hpp>
#include <X-GS/Entity.hpp>

#include <map>

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
        
	private:
		Scene::ScenePtr			createScene(Scenes::ID sceneID);
		
	// Variables (member / properties)
	private:
		sf::RenderWindow&		mWindow;
		Scene::ScenePtr			currentScene;
		std::map<Scenes::ID, std::function<Scene::ScenePtr()>>	mFactories;
    };
	
	// Template implementation
	template <typename T>
	void SceneManager::registerScene(Scenes::ID stateID)
	{
		mFactories[stateID] = [this] ()
		{
			return Scene::ScenePtr(new T(mWindow, *this));
		};
	}
    
} // namespace xgs

#endif // XGS_SCENEMANAGER_HPP