#ifndef YOURGAME_EXAMPLESCENE_HPP
#define YOURGAME_EXAMPLESCENE_HPP

#include <X-GS/Scene.hpp>
#include <X-GS/SceneManager.hpp>
#include <X-GS/ResourceManager.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ResourcePath.hpp"
#include "ResourceIdentifiers.hpp"
#include "ExampleBallEntity.hpp"

//#include <iostream>

class ExampleScene : public xgs::Scene
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
	explicit				ExampleScene(sf::RenderWindow& window, xgs::SceneManager& sceneManager);
	~ExampleScene();
	
	virtual void			update(const xgs::HiResDuration& dt);
	virtual void			render();
	virtual void			handleEvent(const sf::Event& event);
	
private:
	virtual void			buildScene();
	virtual void			loadResources();
	
	// Variables (member / properties)
private:
	TransitionState			mTransitionState;
	xgs::HiResDuration		mTransitionTime;
	xgs::HiResDuration		mTransitionDuration;
	
	sf::RectangleShape		mFadingRectangle;
	sf::Text				mText;
	
	FontManager				mFontManager;
};

#endif // YOURGAME_EXAMPLESCENE_HPP
