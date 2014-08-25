#ifndef YOURGAME_EXAMPLEPLAYERENTITY_HPP
#define YOURGAME_EXAMPLEPLAYERENTITY_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <X-GS/Entity.hpp>
#include <X-GS/PhysicState.hpp>
#include <X-GS/Integrator.hpp>

/*
 Derived class
 */
class ExamplePlayerEntity : public xgs::Entity, public sf::Sprite
{
public:
	ExamplePlayerEntity(sf::FloatRect bounds, sf::Texture& texture);
	virtual					~ExamplePlayerEntity();
	
	virtual void			updateThis(const xgs::HiResDuration& dt);
	virtual void			drawThis(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			handleEventThis(const sf::Event& event);
	
	void					setBounds(sf::FloatRect bounds);
	
private:
	void					handleRealTimeInput();
	
private:
	// Components
	xgs::PhysicState		mPhysics;
	sf::FloatRect			mBounds;
	float					mSpeed;
};

#endif // YOURGAME_EXAMPLEPLAYERENTITY_HPP
