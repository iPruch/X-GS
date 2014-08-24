#include <X-GS/Integrator.hpp>
#include <iostream>

namespace xgs {
    
    // Simple integrator. Accumulates error as time passes.
    void Integrator::Euler(PhysicState& physics,
						   sf::Transformable& transf,
						   const HiResDuration& dt)
    {
        float dtValue = ((float)dt.count()/ONE_SECOND.count());
        
        transf.setPosition(transf.getPosition() + physics.getVelocity() * dtValue);
        physics.setVelocity(physics.getVelocity() + (physics.getForce() / physics.getMass()) * dtValue);		
    }
    
    // More accurate than Euler, but a bit more resource-consuming.
    void Integrator::RK4(PhysicState& physics,
						 sf::Transformable& transf,
						 const HiResDuration& dt)
    {
        float dtValue = ((float)dt.count()/ONE_SECOND.count());
        
        Derivative a,b,c,d;
        Derivative initial;
        
        a = evaluateRK4(physics, transf, HiResDuration::zero(), initial);
        b = evaluateRK4(physics, transf, dt / 2, a);
        c = evaluateRK4(physics, transf, dt / 2, b);
        d = evaluateRK4(physics, transf, dt, c);
        
        sf::Vector2f dpdt = 1.0f / 6.0f *
        ( a.dp + 2.0f * (b.dp + c.dp) + d.dp );
        
        sf::Vector2f dvdt = 1.0f / 6.0f *
        ( a.dv + 2.0f * (b.dv + c.dv) + d.dv );
        
        transf.setPosition(transf.getPosition() + dpdt * dtValue);
        physics.setVelocity(physics.getVelocity() + dvdt * dtValue);
    }
    
    // Auxiliar function for RK4 integrator
    Derivative Integrator::evaluateRK4(const PhysicState& initialPhysics,
									   const sf::Transformable& initialTransf,
									   const HiResDuration& dt,
									   const Derivative& d)
    {
        float dtValue = ((float)dt.count()/ONE_SECOND.count());
        
        PhysicState physics;
		sf::Transformable transf;
        transf.setPosition(initialTransf.getPosition() + d.dp * dtValue); // Add the velocity to position
        physics.setVelocity(initialPhysics.getVelocity() + d.dv * dtValue); // Add the acceleration to velocity
        physics.setForce(initialPhysics.getForce());
        physics.setMass(initialPhysics.getMass());
        
        Derivative output;
        output.dp = physics.getVelocity();
        output.dv = accelerationRK4(physics);
        return output;
    }
    
    // Auxiliar function for RK4 integrator
    sf::Vector2f Integrator::accelerationRK4(const PhysicState& physics)
    {
        return physics.getForce() / physics.getMass();
    }
    
} // namespace xgs
