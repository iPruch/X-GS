#ifndef XGS_INTEGRATOR_HPP
#define XGS_INTEGRATOR_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <X-GS/Time.hpp>
#include <X-GS/PhysicState.hpp>

namespace xgs {
    
	// Needed struct for RK4 method.
    struct Derivative
    {
        sf::Vector2f dp; // dp/dt = velocity
        sf::Vector2f dv; // dv/dt = acceleration
    };
    
	
	// Integrator class. Implements Euler and RK4 integration methods.
    class Integrator
    {
		// Class methods
    public:
        void static                     Euler(PhysicState& physics,
											  sf::Transformable& transf,
                                              const HiResDuration& dt);
        void static                     RK4(PhysicState& physics,
											sf::Transformable& transf,
                                            const HiResDuration& dt);
        
        
    private:
        Derivative static               evaluateRK4(const PhysicState& initialPhysics,
													const sf::Transformable& initialTransf,
                                                    const HiResDuration& dt,
                                                    const Derivative& d);
        sf::Vector2f static             accelerationRK4(const PhysicState&
														physics);
    };
    
} // namespace xgs

#endif // XGS_INTEGRATOR_HPP
