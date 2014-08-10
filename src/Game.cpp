#include <X-GS/Game.hpp>

#include <SFML/Window/Event.hpp>


const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: mWindow(sf::VideoMode(640, 480), "Window Title", sf::Style::Close)
{
    // Resource loading here if needed (RAII)
}

void Game::run()
{
    // Basic game loop
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

            // Input handling call here
            
			update(TimePerFrame);

		}

		render();
	}
}

void Game::update(sf::Time elapsedTime)
{
    // Update calls here
}

void Game::render()
{
	mWindow.clear();	

    // Draw calls here
    
	mWindow.display();
}
