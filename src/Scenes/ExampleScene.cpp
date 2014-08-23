#include <X-GS/Scenes/ExampleScene.hpp>
#include <iostream>

#include "ResourcePath.hpp"

namespace xgs {
	
	ExampleScene::ExampleScene(sf::RenderWindow& window, SceneManager& sceneManager)
	: Scene(window, sceneManager)
	, mTransitionState(none)
	, mTransitionTime(0)
	, mTransitionDuration(ONE_SECOND*3)
	, mFadingRectangle()
	{
		// Load resources here (RAII)
		std::cout << "ExampleScene constructor\n";

		mFont.loadFromFile(resourcePath() + "Sansation.ttf"); // resourcePath() method needs an implementation per platform/OS
        mText.setFont(mFont);
        mText.setPosition(mWindow.getSize().x / 2, mWindow.getSize().y / 2);
        mText.setCharacterSize(32);
        mText.setColor(sf::Color::Black);
		mText.setString("Example Scene 1");
		
		
		// Build the scene graph
		buildScene();
		
		// Begin in transition
		mTransitionState = in;
		
		// Set the rectangle's size. This rectangle is used for the transition effect.
		mFadingRectangle.setSize(sf::Vector2f(mWindow.getView().getSize().x, mWindow.getView().getSize().y));
		mFadingRectangle.setFillColor(sf::Color(0, 0, 0, 255));
		
	}

	void ExampleScene::buildScene()
	{
		sf::FloatRect bounds(0, 0, mWindow.getView().getSize().x, mWindow.getView().getSize().y);
		
		std::unique_ptr<ExampleBallEntity> mainBall(new ExampleBallEntity(bounds));
		mainBall->mTransformable.setPosition(0.f, 0.f);
		
//		std::unique_ptr<ExampleBallEntity> secondBall(new ExampleBallEntity(bounds));
//		mainBall->mTransformable.setPosition(0.f, 30.f);
//		
//		mainBall->attachChild(std::move(secondBall));
		mSceneGraph.attachChild(std::move(mainBall));
	}
	
	void ExampleScene::update(const HiResDuration &dt)
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
				mSceneManager.loadScene(Scenes::Example2);
				break;
		}
	}
	
	void ExampleScene::render()
	{
		// Clear with white color to distinguish this scene from the second one
		mWindow.clear(sf::Color::White);
		
		// Set the view (camera) of this scene
		//mWindow.setView(mSceneView);
		
		// Draw the scene
		mWindow.draw(mSceneGraph);
		
		// Draw text on top of everything
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
	
	ExampleScene::~ExampleScene()
	{
		// Cleanup
		std::cout << "ExampleScene destructor\n";
	}
}