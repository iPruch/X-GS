#include "ExampleBallEntity.hpp"

#include <random>
//#include <iostream>

ExampleBallEntity::ExampleBallEntity(sf::FloatRect bounds)
: mCircle()
, mPhysics()
, mBounds(bounds)
{
	// Load resources here (RAII)
	
	//std::cout << "ExampleBallEntity constructor\n";
	
	// Setup
	mCircle.setRadius(rand() % 50 + 1);
	mCircle.setOrigin(mCircle.getRadius(), mCircle.getRadius());
	mCircle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255.f));
	mCircle.setOutlineColor(sf::Color::White);
	mCircle.setOutlineThickness(1.f);
	
	mTransformable.setPosition(rand() % (int)mBounds.width, rand() % (int)mBounds.height);
	mPhysics.setMass(mCircle.getRadius());
	mPhysics.setVelocity(sf::Vector2f((rand() - rand() * 2) % 100, 0.f));
	mPhysics.setForce(sf::Vector2f(0.f, 9.8f * 20 * mPhysics.getMass())); // Gravity
}

void ExampleBallEntity::updateThis(const xgs::HiResDuration &dt)
{
	// Advance the physics with Euler integration
	xgs::Integrator::Euler(mPhysics, mTransformable, dt);
	
	// Keep the ball inside the bounds
	// Right
	if (mTransformable.getPosition().x > mBounds.left + mBounds.width - mCircle.getRadius()) {
		
		// If velocity is low, stop bouncing
		if (mPhysics.getVelocity().x < -30.f)
			mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x, 0.f));
		
		// Correct position and change velocity to the opposite (bounce)
		mTransformable.setPosition(sf::Vector2f(mBounds.width - mCircle.getRadius(), mTransformable.getPosition().y));
		mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x * (-0.8f), mPhysics.getVelocity().y));
	}
	// Left
	else if (mTransformable.getPosition().x < mBounds.left + mCircle.getRadius()) {
		
		if (mPhysics.getVelocity().x > 30.f)
			mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x, 0.f));
		
		mTransformable.setPosition(sf::Vector2f(mCircle.getRadius(), mTransformable.getPosition().y));
		mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x * (-0.8f), mPhysics.getVelocity().y));
	}
	// Bottom
	if (mTransformable.getPosition().y > mBounds.top + mBounds.height - mCircle.getRadius()) {
		
		if (mPhysics.getVelocity().y < 30.f)
			mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x, 0.f));
		
		mTransformable.setPosition(sf::Vector2f(mTransformable.getPosition().x, mBounds.height - mCircle.getRadius()));
		mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x *  (0.99f), mPhysics.getVelocity().y * (-0.8f)));
	}
	// Top
	else if (mTransformable.getPosition().y < mBounds.top + mCircle.getRadius()) {
		
		if (mPhysics.getVelocity().y > -30.f)
			mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x, 0.f));
		
		mTransformable.setPosition(sf::Vector2f(mTransformable.getPosition().x, mBounds.top + mCircle.getRadius()));
		mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x *  (0.99f), mPhysics.getVelocity().y * (-0.8f)));
	}
}

void ExampleBallEntity::drawThis(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(mCircle, states);
}

void ExampleBallEntity::handleEventThis(const sf::Event& event)
{
	//std::cout << "Event reaches ExampleBallEntity" << std::endl;
	
	if (event.type == sf::Event::KeyPressed)
	{
		// G key - Toggle gravity
		if (event.key.code == sf::Keyboard::G)
			mPhysics.setForce(sf::Vector2f(0.f, 0.f));
		
		// Arrow keys - Change gravity direction
		if (event.key.code == sf::Keyboard::Up)
			mPhysics.setForce(sf::Vector2f(0.f, -9.8f * 20 * mPhysics.getMass()));
		if (event.key.code == sf::Keyboard::Down)
			mPhysics.setForce(sf::Vector2f(0.f, 9.8f * 20 * mPhysics.getMass()));
		if (event.key.code == sf::Keyboard::Left)
			mPhysics.setForce(sf::Vector2f(-9.8f * 20 * mPhysics.getMass(), 0.f));
		if (event.key.code == sf::Keyboard::Right)
			mPhysics.setForce(sf::Vector2f(9.8f * 20 * mPhysics.getMass(), 0.f));
		
	}
}

void ExampleBallEntity::setBounds(sf::FloatRect bounds)
{
	mBounds = bounds;
}


ExampleBallEntity::~ExampleBallEntity()
{
	// Cleanup
	//std::cout << "ExampleBallEntity destructor\n";
}
