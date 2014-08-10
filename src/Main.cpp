#include <X-GS/Game.hpp>
#include <stdexcept>
#include <iostream>


int main()
{
    // General try-catch for unhandled exceptions in game
	try
	{
        // Simply instantiate the game and run it
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
