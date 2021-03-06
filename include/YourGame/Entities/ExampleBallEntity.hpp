#ifndef YOURGAME_EXAMPLEBALLENTITY_HPP
#define YOURGAME_EXAMPLEBALLENTITY_HPP

#include <SFML/Graphics/CircleShape.hpp>

#include <X-GS/Entity.hpp>
#include <X-GS/PhysicState.hpp>
#include <X-GS/Integrator.hpp>

//#include <iostream>

/*
 Derived class from xgs::Entity
 */
class ExampleBallEntity : public xgs::Entity
{
public:
						ExampleBallEntity(sf::FloatRect bounds);
	virtual				~ExampleBallEntity();
	
	void				updateThis(const xgs::HiResDuration& dt) override;
	void				drawThis(sf::RenderTarget& target, sf::RenderStates states) const override;
	void				handleEventThis(const sf::Event& event) override;
	
	void				setBounds(sf::FloatRect bounds);
	
private:
	// Components
	sf::CircleShape		mCircle;
	sf::FloatRect		mBounds;
	xgs::PhysicState	mPhysics;
};

#endif // YOURGAME_EXAMPLEBALLENTITY_HPP
