#ifndef XGS_EXAMPLESCENE_HPP
#define XGS_EXAMPLESCENE_HPP

#include <X-GS/Scene.hpp>
#include <X-GS/Entities/ExampleBallEntity.hpp>
#include <X-GS/SceneManager.hpp>
#include <X-GS/ResourceManager.hpp>
#include <X-GS/ResourceIdentifiers.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace xgs {
	
    class ExampleScene : public Scene
    {
	// Typedefs and enumerations
	private:
		enum TransitionState {
			none,
			in,
			inFinished,
			out,
			outFinished
		};
		
	// Methods
	public:
		explicit				ExampleScene(sf::RenderWindow& window, SceneManager& sceneManager);
								~ExampleScene();
			     
		virtual void			update(const HiResDuration& dt);
		virtual void			render();
		virtual void			handleEvent(const sf::Event& event);

	private:
		virtual void			buildScene();
		virtual void			loadResources();
			
	// Variables (member / properties)
	private:
		TransitionState			mTransitionState;
		HiResDuration			mTransitionTime;
		HiResDuration			mTransitionDuration;
		
		sf::RectangleShape		mFadingRectangle;
		sf::Text				mText;
		
		FontManager				mFontManager;
    };
    
} // namespace xgs

#endif // XGS_EXAMPLESCENE_HPP
