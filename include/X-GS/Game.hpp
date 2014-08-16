#ifndef XGS_GAME_HPP
#define XGS_GAME_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <X-GS/Integrator.hpp>

namespace xgs {
    
    class Game : private sf::NonCopyable
    {
    public:
        Game();
        void                    runFixedDeltaTime();
        void                    runVariableDeltaTime();
        void                    runSemiFixedDeltaTime();
        void                    runFixedSimulationVariableFramerate();
        
	private:
        void                    update(const HiResDuration &dt);
        void                    render();
        void                    updateStatistics(const HiResDuration &elapsedTime);
        
        
	private:
        sf::RenderWindow        mWindow;
        
        bool                    mVSync;
        
        // Statistics
        HiResDuration           mTimeSinceStart; // Accumulator of all time
        sf::Font                mFont;
        sf::Text                mStatisticsText;
        HiResDuration           mStatisticsUpdateTime;
        std::size_t             mStatisticsNumFrames;
    };
    
} // namespace xgs

#endif // XGS_GAME_HPP
