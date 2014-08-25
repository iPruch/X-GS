#ifndef XGS_GAME_HPP
#define XGS_GAME_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <X-GS/Integrator.hpp>
#include <X-GS/SceneManager.hpp>
#include <X-GS/ResourceManager.hpp>

#include <iostream>

#include "ScenesIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "ExampleScene.hpp"
#include "ExampleScene2.hpp"

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
	void									update(const xgs::HiResDuration& dt);
	void									render();
	void									handleEvents();
	void									updateStatistics(const xgs::HiResDuration& elapsedTime);
	
	void									loadGeneralResources();
	
	// Variables (member / properties)
private:
	sf::RenderWindow						mWindow;
	bool									mVSync;
	xgs::SceneManager						mSceneManager;
	sf::Event								mEvent;
	
	// Resources managers
	FontManager								mFontManager;
	
	// Statistics
	xgs::HiResDuration						mTimeSinceStart; // Accumulator of all time
	sf::Text								mStatisticsText;
	xgs::HiResDuration						mStatisticsUpdateTime;
	std::size_t								mStatisticsNumFrames;
};

#endif // XGS_GAME_HPP
