#include <X-GS/Integrator.hpp>
#include <iostream>

namespace xgs {
    
    // Simple integrator. Accumulates error as time passes.
    void Integrator::Euler(State &state,
                           const HiResDuration &dt)
    {
        float dtValue = ((float)dt.count()/ONE_SECOND.count());
        
        state.position = state.position + state.velocity * dtValue;
        state.velocity = state.velocity + (state.force / state.mass) * dtValue;
    }
    
    // More accurate than Euler.
    // NOTE: It behaves differently (slowly?) than Euler regarding to forces/acceleration. I believe is a bug. I'll check it later.
    void Integrator::RK4(State &state,
                         const HiResDuration &dt)
    {
        float dtValue = ((float)dt.count()/ONE_SECOND.count());
        
        Derivative a,b,c,d;
        Derivative initial;
        
        a = evaluateRK4(state, HiResDuration::zero(), initial);
        b = evaluateRK4(state, dt / 2, a);
        c = evaluateRK4(state, dt / 2, b);
        d = evaluateRK4(state, dt, c);
        
        sf::Vector2f dpdt = 1.0f / 6.0f *
        ( a.dp + 2.0f * (b.dp + c.dp) + d.dp );
        
        sf::Vector2f dvdt = 1.0f / 6.0f *
        ( a.dv + 2.0f * (b.dv + c.dv) + d.dv );
        
        state.position = state.position + dpdt * dtValue;
        state.velocity = state.velocity + dvdt * dtValue;
    }
    
    // Auxiliar function for RK4 integrator
    Derivative Integrator::evaluateRK4(const State &initial,
                                       const HiResDuration &dt,
                                       const Derivative &d)
    {
        float dtValue = ((float)dt.count()/ONE_SECOND.count());
        
        State state;
        state.position = initial.position + d.dp * dtValue; // Add the velocity to position
        state.velocity = initial.velocity + d.dv * dtValue; // Add the acceleration to velocity
        state.force = initial.force;
        state.mass = initial.mass;
        
        Derivative output;
        output.dp = state.velocity;
        output.dv = accelerationRK4(state, dt);
        return output;
    }
    
    // Auxiliar function for RK4 integrator
    sf::Vector2f Integrator::accelerationRK4(const State &state,
                                             const HiResDuration &dt)
    {
        float dtValue = ((float)dt.count()/ONE_SECOND.count());
        
        return state.force / state.mass * dtValue;
    }
    
} // namespace xgs
