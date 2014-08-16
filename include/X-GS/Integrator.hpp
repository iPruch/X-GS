#ifndef XGS_INTEGRATOR_HPP
#define XGS_INTEGRATOR_HPP

#include <SFML/System/Vector2.hpp>
#include <chrono>

// One second in nanoseconds
#define ONE_SECOND (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)))

namespace xgs {
    
    // std::chrono shortcuts
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> HiResTime;
    typedef std::chrono::nanoseconds HiResDuration;
    typedef std::chrono::high_resolution_clock HiResClock;
    
    // Recommended struct for objects which will be
    struct State
    {
        sf::Vector2f position;
        sf::Vector2f velocity;
        
        sf::Vector2f force;
        float mass = 1;
    };
    
    struct Derivative
    {
        sf::Vector2f dp; // dp/dt = velocity
        sf::Vector2f dv; // dv/dt = acceleration
    };
    
    class Integrator
    {
    public:
        void static                     Euler(State &state,
                                              const HiResDuration &dt);
        void static                     RK4(State &state,
                                            const HiResDuration &dt);
        
        
    private:
        Derivative static               evaluateRK4(const State &initial,
                                                    const HiResDuration &dt,
                                                    const Derivative &d);
        sf::Vector2f static             accelerationRK4(const State &state);
    };
    
} // namespace xgs

#endif // XGS_INTEGRATOR_HPP
