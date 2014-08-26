#include "ExamplePlayerEntity.hpp"

ExamplePlayerEntity::ExamplePlayerEntity(sf::FloatRect bounds, sf::Texture& texture)
: mPhysics()
, mBounds(bounds)
, mSpeed(200.f)
{
	// Load resources here (RAII)
	
	setTexture(texture);
	
	//std::cout << "ExampleBallEntity constructor\n";
	
	// Setup
	mTransformable.setPosition(mBounds.width / 2, mBounds.height / 2);
}

void ExamplePlayerEntity::updateThis(const xgs::HiResDuration &dt)
{
	// Handle real-time input
	handleRealTimeInput();
	
	// Advance the physics with Euler integration
	xgs::Integrator::Euler(mPhysics, mTransformable, dt);
	
	// Keep the player inside the specified bounds
	// Right
	if (mTransformable.getPosition().x > mBounds.left + mBounds.width - getLocalBounds().width) {
		mTransformable.setPosition(sf::Vector2f(mBounds.left + mBounds.width - getLocalBounds().width, mTransformable.getPosition().y));
		mPhysics.setVelocity(sf::Vector2f(0.f, mPhysics.getVelocity().y));
	}
	// Left
	else if (mTransformable.getPosition().x < mBounds.left) {
		
		mTransformable.setPosition(sf::Vector2f(mBounds.left, mTransformable.getPosition().y));
		mPhysics.setVelocity(sf::Vector2f(0.f, mPhysics.getVelocity().y));
	}
	// Bottom
	if (mTransformable.getPosition().y > mBounds.top + mBounds.height - getLocalBounds().height) {
		
		mTransformable.setPosition(sf::Vector2f(mTransformable.getPosition().x, mBounds.top + mBounds.height - getLocalBounds().height));
		mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x, 0.f));
	}
	// Top
	else if (mTransformable.getPosition().y < mBounds.top) {
		
		mTransformable.setPosition(sf::Vector2f(mTransformable.getPosition().x, mBounds.top));
		mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x, 0.f));
	}
	
	/* Reduce previous velocity (until the player stops moving).
	 This won't affect in a direction if a that direction key is
	 pressed.
	 This need vSync enabled. Using dt here is difficult because
	 PhysicState lacks some features. If it had some kind of
	 airFriction, this wouldn't be needed. */
	mPhysics.setVelocity(mPhysics.getVelocity() * 0.9f);
}

void ExamplePlayerEntity::drawThis(sf::RenderTarget &target, sf::RenderStates states) const
{
	// static_cast as sf::Sprite this Entity to draw it
	target.draw(static_cast<sf::Sprite>(*this), states);
}

void ExamplePlayerEntity::handleEventThis(const sf::Event& event)
{
	//std::cout << "Event reaches ExampleBallEntity" << std::endl;
	
	if (event.type == sf::Event::KeyPressed)
	{
		// G key - Switch gravity (up/down)
		if (event.key.code == sf::Keyboard::G)
			mPhysics.setForce(sf::Vector2f(0.f, mPhysics.getForce().y * (-1.f)));
	}
}

void ExamplePlayerEntity::handleRealTimeInput()
{
	// Real-time input does not use Events. You only need to invoke the required static (class) method:
	
	// Basic Keyboard controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		mPhysics.setVelocity(sf::Vector2f(-mSpeed, mPhysics.getVelocity().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		mPhysics.setVelocity(sf::Vector2f(mSpeed, mPhysics.getVelocity().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x, -mSpeed));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x, mSpeed));
	}
	
	// Basic Joystick controls
	if (sf::Joystick::isConnected(0)) // Is joystick 0 connected?
	{
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		
		mPhysics.setVelocity(sf::Vector2f(x * mSpeed, y * mSpeed));
	}
	
	// Controls dynamic binding can be also implemented for the player to configure the desired controls, but I'll keep this example simple.
	
	/*
	 You can handle more kinds of events here, but remember first
	 to propagate them from Game class, at Game::handleEvents method
	 and from the scene class which owns this entity.
	 */
}

void ExamplePlayerEntity::setBounds(sf::FloatRect bounds)
{
	mBounds = bounds;
}


ExamplePlayerEntity::~ExamplePlayerEntity()
{
	// Cleanup
}
