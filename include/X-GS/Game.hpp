#ifndef XGS_GAME_HPP
#define XGS_GAME_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Game : private sf::NonCopyable
{
	public:
								Game();
		void					run();
		

	private:
		void					update(sf::Time elapsedTime);
		void					render();
		

	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
};

#endif // XGS_GAME_HPP
