#include <X-GS/PhysicState.hpp>
#include <cassert>

namespace xgs {
	
	// Constructor
	PhysicState::PhysicState()
	: mVelocity()
	, mForce()
	, mMass(1.f)
	{
		
	}
	
	void PhysicState::setVelocity(sf::Vector2f velocity)
	{
		mVelocity = velocity;
	}
	
	const sf::Vector2f PhysicState::getVelocity() const
	{
		return mVelocity;
	}
	
	void PhysicState::setForce(sf::Vector2f force)
	{
		mForce = force;
	}
	
	const sf::Vector2f PhysicState::getForce() const
	{
		return mForce;
	}
	
	void PhysicState::setMass(float mass)
	{
		assert(mass > 0);
		mMass = mass;
	}
	
	const float PhysicState::getMass() const
	{
		return mMass;
	}
	
} // namespace xgs
