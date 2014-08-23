#include <X-GS/Entities/ExampleBallEntity.hpp>
#include <random>
#include <iostream>

using namespace xgs;

ExampleBallEntity::ExampleBallEntity(sf::FloatRect bounds)
	: mCircle()
	, mPhysics()
	, mBounds(bounds)
	{
		// Load resources here (RAII)
		std::cout << "ExampleBallEntity constructor\n";
				
		// Setup
		mCircle.setRadius(rand() % 50 + 1);
		mCircle.setOrigin(mCircle.getRadius(), mCircle.getRadius());
		mCircle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255.f));
		mCircle.setOutlineColor(sf::Color::White);
		mCircle.setOutlineThickness(1.f);
		
		mTransformable.setPosition(rand() % (int)mBounds.width, rand() % (int)mBounds.height);
		mPhysics.setMass(mCircle.getRadius());
		mPhysics.setVelocity(sf::Vector2f((rand() - rand()*2) % 100, 0.f));
		mPhysics.setForce(sf::Vector2f(0.f, 9.8 * mPhysics.getMass() * 20)); // Gravity
		
		mCircle.setPosition(mTransformable.getPosition());
	}

	void ExampleBallEntity::updateThis(const HiResDuration &dt)
	{
		// Advance the physics with Euler integration
		Integrator::Euler(mPhysics, mTransformable, dt);
		
		if (mTransformable.getPosition().x > mBounds.left + mBounds.width - mCircle.getRadius()) {
			mTransformable.setPosition(sf::Vector2f(mBounds.width - mCircle.getRadius(), mTransformable.getPosition().y));
			mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x * (-1.f), mPhysics.getVelocity().y));
		}
		else if (mTransformable.getPosition().x < mBounds.left + mCircle.getRadius()) {
			mTransformable.setPosition(sf::Vector2f(mCircle.getRadius(), mTransformable.getPosition().y));
			mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x * (-1.f), mPhysics.getVelocity().y));
		}
		
		if (mTransformable.getPosition().y > mBounds.top + mBounds.height - mCircle.getRadius()) {
			mTransformable.setPosition(sf::Vector2f(mTransformable.getPosition().x, mBounds.height - mCircle.getRadius()));
			mPhysics.setVelocity(sf::Vector2f(mPhysics.getVelocity().x, mPhysics.getVelocity().y * (-1.f)));
		}
	}
	
	void ExampleBallEntity::drawThis(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(mCircle, states);
	}

	void ExampleBallEntity::setBounds(sf::FloatRect bounds)
	{
		mBounds = bounds;
	}


	ExampleBallEntity::~ExampleBallEntity()
	{
		// Cleanup
		std::cout << "ExampleBallEntity destructor\n";
	}
