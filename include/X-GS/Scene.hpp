#ifndef XGS_SCENE_HPP
#define XGS_SCENE_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <X-GS/SceneGraphNode.hpp>
#include <X-GS/Scenes/ScenesIdentifiers.hpp>

namespace xgs {
    
	// Forward declaration. You must include this class in the classes you create which inherit from Scene
	class SceneManager;
	
	/*
	 The Scene class is an abstract class to be inherited and implemented
	 by your scenes classes. For example, you can create a Level1Scene.hpp/cpp,
	 inherit from Scene and implement buildScene, update and draw.
	 
	 buildScene() method creates the scene graph structure. This method is
	 where you should attach childs to the scene graph, initialize them,
	 etc.
	 
	 update() method will be called to advance the simulation and the logic
	 of the game. There you can put some of the logic (check if the level
	 has ended or something similiar) or simply invoke the update method
	 of the scene graph to update all scene graph nodes of this scene.
	 Here you can also implement level loading/switching, pause, a menu...
	 
	 render() method will be called for rendering. Inside of it you can
	 perform specific drawing for this scene (pause menu, GUI, etc.) and
	 invoke the draw method of all scene graph nodes.
	 */
	
    class Scene : private sf::NonCopyable
    {
	// Typedefs and enumerations
	public:
		typedef std::unique_ptr<Scene>		ScenePtr;
		
	// Methods
	public:
		explicit							Scene(sf::RenderWindow& window, SceneManager& sceneManager) : mWindow(window), mSceneView(mWindow.getView()), mSceneGraph(), mSceneManager(sceneManager){}
		virtual								~Scene(){}
		
		virtual void						buildScene() = 0;
		
		virtual void						update(const HiResDuration& dt) = 0;
		virtual void						render() = 0;
    
	// Variables (member / properties)
	protected:
		sf::RenderWindow&					mWindow;
		sf::View							mSceneView; // Camera
		SceneGraphNode						mSceneGraph;
		SceneManager&						mSceneManager;
	};
    
} // namespace xgs

#endif // XGS_SCENE_HPP
