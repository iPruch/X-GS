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
#include <X-GS/ResourceManager.hpp>
#include <X-GS/ResourceIdentifiers.hpp>

#include <iostream>

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
		void									handleEvents();
		void									updateStatistics(const HiResDuration& elapsedTime);
		
		void									loadGeneralResources();
        
	// Variables (member / properties)
	private:
		sf::RenderWindow						mWindow;
		bool									mVSync;
		SceneManager							mSceneManager;
		sf::Event								mEvent;
		
		// Resources managers
		FontManager								mFontManager;
		
		// Statistics
		HiResDuration							mTimeSinceStart; // Accumulator of all time
		sf::Text								mStatisticsText;
		HiResDuration							mStatisticsUpdateTime;
		std::size_t								mStatisticsNumFrames;
    };
    
} // namespace xgs

#endif // XGS_GAME_HPP
