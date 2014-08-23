#ifndef XGS_GAME_HPP
#define XGS_GAME_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <X-GS/Integrator.hpp>
#include <X-GS/Scenes/ExampleScene.hpp>
#include <X-GS/Scenes/ExampleScene2.hpp>
#include <X-GS/Scenes/ScenesIdentifiers.hpp>
#include <X-GS/SceneManager.hpp>

namespace xgs {
    
    class Game : private sf::NonCopyable
    {
	// Methods
	public:
		explicit								Game();
		void									runFixedDeltaTime();
		void									runVariableDeltaTime();
		void									runSemiFixedDeltaTime();
		void									runFixedSimulationVariableFramerate();
        
	private:
		void									update(const HiResDuration& dt);
		void									render();
		void									updateStatistics(const HiResDuration& elapsedTime);
        
	// Variables (member / properties)
	private:
		sf::RenderWindow						mWindow;
		bool									mVSync;
		SceneManager							mSceneManager;
        
		// Statistics
		HiResDuration							mTimeSinceStart; // Accumulator of all time
		sf::Font								mFont;
		sf::Text								mStatisticsText;
		HiResDuration							mStatisticsUpdateTime;
		std::size_t								mStatisticsNumFrames;
    };
    
} // namespace xgs

#endif // XGS_GAME_HPP
