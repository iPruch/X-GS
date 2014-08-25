#include <X-GS/Scenes/ExampleScene.hpp>
#include <iostream>

#include "ResourcePath.hpp"

namespace xgs {
	
	ExampleScene::ExampleScene(sf::RenderWindow& window, SceneManager& sceneManager)
	: Scene(window, sceneManager)
	, mTransitionState(none)
	, mTransitionTime(0)
	, mTransitionDuration(ONE_SECOND*2)
	, mFadingRectangle()
	, mFontManager()
	{
		std::cout << "ExampleScene constructor\n";

		// Load resources here (RAII)
		loadResources();
		
		mText.setFont(mFontManager.get(Fonts::Sansation, FontManager::Global));
        mText.setPosition(mWindow.getSize().x / 2, 5.f);
        mText.setCharacterSize(20);
        mText.setColor(sf::Color::Black);
		mText.setString("Example Scene 1\n N - Next scene\n G - No gravity\n Arrows -  gravity direction");
		
		
		// Build the scene graph
		buildScene();
		
		// Begin in transition
		mTransitionState = in;
		
		// Set the rectangle's size. This rectangle is used for the transition effect.
		mFadingRectangle.setSize(sf::Vector2f(mWindow.getView().getSize().x, mWindow.getView().getSize().y));
		mFadingRectangle.setFillColor(sf::Color(0, 0, 0, 255));
		
	}

	void ExampleScene::loadResources()
	{
		// Load this scene specific resources
	}
	
	void ExampleScene::buildScene()
	{
		sf::FloatRect bounds(0, 0, mWindow.getView().getSize().x, mWindow.getView().getSize().y);
		
		// Instantiate 200 balls
		for (int i = 0; i < 200; i++) {
			std::unique_ptr<ExampleBallEntity> ball(new ExampleBallEntity(bounds));
			
			// Add each ball to the scene graph (as children of the root node)
			mSceneGraph.attachChild(std::move(ball));
		}

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
	
	void ExampleScene::handleEvent(const sf::Event& event)
	{
		// Perform appropiate actions (only if not in middle of a transition)
		if (event.type == sf::Event::KeyPressed && mTransitionState != (in || out))
		{
			// N key - Next scene (ExampleScene2)
			if (event.key.code == sf::Keyboard::N)
				mTransitionState = out;
			
			// Propagate event handling to entities in the scene graph
			mSceneGraph.handleEvent(event);
		}
	}
	
	ExampleScene::~ExampleScene()
	{
		// Cleanup
		std::cout << "ExampleScene destructor\n";
	}
}