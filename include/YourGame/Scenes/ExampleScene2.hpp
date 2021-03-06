#ifndef YOURGAME_EXAMPLESCENE2_HPP
#define YOURGAME_EXAMPLESCENE2_HPP

#include <X-GS/Scene.hpp>
#include <X-GS/SceneManager.hpp>
#include <X-GS/ResourceManager.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ResourcePath.hpp"
#include "ResourceIdentifiers.hpp"
#include "ExamplePlayerEntity.hpp"

//#include <iostream>

class ExampleScene2 : public xgs::Scene
{
private:
	// Typedefs and enumerations
	enum TransitionState {
		none,
		in,
		inFinished,
		out,
		outFinished
	};
	
	// Methods
public:
	explicit				ExampleScene2(sf::RenderWindow& window, xgs::SceneManager& sceneManager);
							~ExampleScene2();
	
	void					update(const xgs::HiResDuration& dt) override;
	void					render() override;
	void					handleEvent(const sf::Event& event) override;
	
private:
	void					buildScene() override;
	void					loadResources() override;
	
	// Variables (member / properties)
private:
	TransitionState			mTransitionState;
	xgs::HiResDuration		mTransitionTime;
	xgs::HiResDuration		mTransitionDuration;
	
	sf::RectangleShape		mBackground;
	sf::RectangleShape		mFadingRectangle;
	sf::Text				mText;
	
	FontManager				mFontManager;
	TextureManager			mTextureManager;
};

#endif // YOURGAME_EXAMPLESCENE2_HPP
