#include "Game.hpp"

#include <stdexcept>
#include <iostream>

int main()
{
    // General try-catch for unhandled exceptions in game
	try
	{
        // Simply instantiate the game and run it
		Game game;
        
        // Choose from these run methods according to your requirements
		//game.runFixedDeltaTime();
		//game.runVariableDeltaTime();
		game.runSemiFixedDeltaTime();
		//game.runFixedSimulationVariableFramerate();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
