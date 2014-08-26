#ifndef XGS_PHYSICSTATE_HPP
#define XGS_PHYSICSTATE_HPP

#include <SFML/System/Vector2.hpp>

namespace xgs {
	
	// Needed struct for entities updated with the Integrator class.
	class PhysicState
	{
		// Methods
	public:
						PhysicState();
		void				setVelocity(sf::Vector2f velocity);
		void				setForce(sf::Vector2f force);
		void				setMass(float mass);
		
		const sf::Vector2f		getVelocity() const;
		const sf::Vector2f		getForce() const;
		const float			getMass() const;
		
		// Variables (member / properties)
	private:
		//sf::Vector2f position; // Get position from transform
		sf::Vector2f			mVelocity;
		sf::Vector2f			mForce;
		float				mMass;
    };
	
} // namespace xgs

#endif // XGS_PHYSICSTATE_HPP
