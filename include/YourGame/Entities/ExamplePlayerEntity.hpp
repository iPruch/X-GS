#ifndef YOURGAME_EXAMPLEPLAYERENTITY_HPP
#define YOURGAME_EXAMPLEPLAYERENTITY_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <X-GS/Entity.hpp>
#include <X-GS/PhysicState.hpp>
#include <X-GS/Integrator.hpp>

/*
 Derived class from xgs::Entity and sf::Sprite
 
 You can also have sf::Sprite as a member variable. In fact, with
 that approach you could have multiple sprites per entity. This
 can come in handy if your entity has different graphical parts
 (i.e, clothes, helmet, weapon...). In that case you should change
 ExamplePlayerEntity::drawThis implementation to draw all your
 sprites instead of (*this) and stop inheriting from sf::Sprite
 */
class ExamplePlayerEntity : public xgs::Entity, public sf::Sprite
{
public:
							ExamplePlayerEntity(sf::FloatRect bounds, sf::Texture& texture);
	virtual					~ExamplePlayerEntity();
	
	void					updateThis(const xgs::HiResDuration& dt) override;
	void					drawThis(sf::RenderTarget& target, sf::RenderStates states) const override;
	void					handleEventThis(const sf::Event& event) override;
	
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
