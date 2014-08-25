#include "ExampleScene2.hpp"

ExampleScene2::ExampleScene2(sf::RenderWindow& window, xgs::SceneManager& sceneManager)
: Scene(window, sceneManager)
, mTransitionState(none)
, mTransitionTime(0)
, mTransitionDuration(ONE_SECOND*2)
, mFadingRectangle()
, mFontManager()
, mTextureManager()
{
	//std::cout << "ExampleScene2 constructor\n";
	
	// Load resources here (RAII)
	loadResources();
	
	// Build the scene graph
	buildScene();
	
	// Some configuration
	mText.setFont(mFontManager.get(Fonts::Sansation, FontManager::Global));
	mText.setPosition(mWindow.getSize().x / 2, 5.f);
	mText.setCharacterSize(20);
	mText.setColor(sf::Color::White);
	mText.setString("Example Scene 2 \n B - Back to previous scene \n Arrows/WASD - Move player");
	
	// Begin in transition
	mTransitionState = in;
	
	// Set the rectangle's size. This rectangle is used for the transition effect.
	mFadingRectangle.setSize(sf::Vector2f(mWindow.getView().getSize().x, mWindow.getView().getSize().y));
	mFadingRectangle.setFillColor(sf::Color(0, 0, 0, 255));
}

void ExampleScene2::loadResources()
{
	// Load this scene specific resources
	mTextureManager.load(Textures::ExamplePlayer, "playerShip.gif");
}

void ExampleScene2::buildScene()
{
	/* Build the scene here: Instantiate and initalize needed
	 entities and attach them to the scene graph with the order
	 you need (i.e. all entities at root, or some at root and
	 some as child of the previous, etc.)
	 */
	
	sf::FloatRect bounds(0, 0, mWindow.getView().getSize().x, mWindow.getView().getSize().y);
	
	std::unique_ptr<ExamplePlayerEntity> player(new ExamplePlayerEntity(bounds, mTextureManager.get(Textures::ExamplePlayer)));
	
	mSceneGraph.attachChild(std::move(player));
}

void ExampleScene2::update(const xgs::HiResDuration &dt)
{
	/* General scene's logic here.
	 You must also invoke the scene graph's update method
	 so that all entities update their state.
	 */
	
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
				mTransitionTime = xgs::HiResDuration(0);
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

void ExampleScene2::handleEvent(const sf::Event& event)
{
	// Perform appropiate actions (only if not in middle of a transition)
	if (event.type == sf::Event::KeyPressed && mTransitionState != (in || out))
	{
		// B key - Back to ExampleScene
		if (event.key.code == sf::Keyboard::B)
			mTransitionState = out;
		
		// Propagate event handling to entities in the scene graph
		mSceneGraph.handleEvent(event);
	}
}

ExampleScene2::~ExampleScene2()
{
	// Cleanup here
	
	//std::cout << "ExampleScene2 destructor\n";
}
