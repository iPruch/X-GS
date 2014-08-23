#include <X-GS/Scenes/ExampleScene2.hpp>
#include <iostream>

#include "ResourcePath.hpp"

namespace xgs {
	
	ExampleScene2::ExampleScene2(sf::RenderWindow& window, SceneManager& sceneManager)
	: Scene(window, sceneManager)
	, mTransitionState(none)
	, mTransitionTime(0)
	, mTransitionDuration(ONE_SECOND*3)
	, mFadingRectangle()
	{
		// Load resources here (RAII)
		std::cout << "ExampleScene2 constructor\n";

		mFont.loadFromFile(resourcePath() + "Sansation.ttf"); // resourcePath() method needs an implementation per platform/OS
        mText.setFont(mFont);
        mText.setPosition(mWindow.getSize().x / 2, mWindow.getSize().y / 2);
        mText.setCharacterSize(32);
        mText.setColor(sf::Color::White);
		mText.setString("Example Scene 2");
		
		// Build the scene graph
		buildScene();
		
		
		// Begin in transition
		mTransitionState = in;
		
		// Set the rectangle's size. This rectangle is used for the transition effect.
		mFadingRectangle.setSize(sf::Vector2f(mWindow.getView().getSize().x, mWindow.getView().getSize().y));
		mFadingRectangle.setFillColor(sf::Color(0, 0, 0, 255));
	}

	void ExampleScene2::buildScene()
	{

	}
	
	void ExampleScene2::update(const HiResDuration &dt)
	{
		mSceneGraph.update(dt);
		
		// Update transition
		switch (mTransitionState) {
			case none:
				break;
				
			case in:
				// Decrease opacity as time moves forward
				mFadingRectangle.setFillColor(sf::Color(0, 0, 0,
														255 - (float)mTransitionTime.count() / (float)mTransitionDuration.count() * 255.f));
				
				mTransitionTime += dt;
				
				// If the transition time has passed, change state to finished.
				if (mTransitionTime >= mTransitionDuration) {
					mTransitionState = inFinished;
					mTransitionTime = HiResDuration(0);
				}
				break;
				
			case inFinished:
				mTransitionTime += dt;
				
				if (mTransitionTime >= ONE_SECOND*3) {
					mTransitionState = out;
					mTransitionTime = HiResDuration(0);
				}
				break;
				
			case out:
				// Increase opacity as time moves forward
				mFadingRectangle.setFillColor(sf::Color(0, 0, 0,
														(float)mTransitionTime.count() / (float)mTransitionDuration.count() * 255.f));
				
				mTransitionTime += dt;
				
				// If the transition time has passed, change state to finished.
				if (mTransitionTime >= mTransitionDuration)
					mTransitionState = outFinished;
				break;
				
			case outFinished:
				mFadingRectangle.setFillColor(sf::Color::Black);
				
				// Load the next scene
				mSceneManager.loadScene(Scenes::Example);
				break;
		}
	}
	
	void ExampleScene2::render()
	{
		// Clear with blue color to distinguish this scene from the first one
		mWindow.clear(sf::Color::Blue);
		mWindow.setView(mSceneView);
		mWindow.draw(mSceneGraph);
		mWindow.draw(mText);
		
		switch (mTransitionState) {
			case none:
				break;
				
			case in:
				mWindow.draw(mFadingRectangle);
				break;
				
			case inFinished:
				break;
				
			case out:
				mWindow.draw(mFadingRectangle);
				break;
				
			case outFinished:
				mWindow.draw(mFadingRectangle);
				break;
		}
	}
	
	ExampleScene2::~ExampleScene2()
	{
		std::cout << "ExampleScene2 destructor\n";
	}
}