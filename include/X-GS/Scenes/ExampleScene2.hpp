#ifndef XGS_EXAMPLESCENE2_HPP
#define XGS_EXAMPLESCENE2_HPP

#include <X-GS/Scene.hpp>
#include <X-GS/Entities/ExampleBallEntity.hpp>

#include <X-GS/SceneManager.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace xgs {
    
    class ExampleScene2 : public Scene
    {
	private:
		enum TransitionState {
			none,
			in,
			inFinished,
			out,
			outFinished
		};
		
		
	public:
		explicit				ExampleScene2(sf::RenderWindow& window, SceneManager& sceneManager);
								~ExampleScene2();
			     
	public:
		virtual void			buildScene();
		virtual void			update(const HiResDuration& dt);
		virtual void			render();
		
	private:
		TransitionState			mTransitionState;
		HiResDuration			mTransitionTime;
		HiResDuration			mTransitionDuration;
		
		sf::RectangleShape		mFadingRectangle;
		
		sf::Font				mFont;
		sf::Text				mText;
    };
    
} // namespace xgs

#endif // XGS_EXAMPLESCENE2_HPP
