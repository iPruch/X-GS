#ifndef XGS_EXAMPLEPLAYERENTITY_HPP
#define XGS_EXAMPLEPLAYERENTITY_HPP

#include <SFML/Graphics/RenderTarget.hpp> // Completes the RenderTarget forward declaration in Drawable, inherited from Entity <- SceneGrahpNode
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <X-GS/Entity.hpp>
#include <X-GS/PhysicState.hpp>
#include <X-GS/Integrator.hpp>

using namespace xgs;

/*
 Derived class
 */
class ExamplePlayerEntity : public Entity, public sf::Sprite
{
public:
	ExamplePlayerEntity(sf::FloatRect bounds, sf::Texture& texture);
	virtual					~ExamplePlayerEntity();
	
	virtual void			updateThis(const HiResDuration& dt);
	virtual void			drawThis(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			handleEventThis(const sf::Event& event);
	
	void					setBounds(sf::FloatRect bounds);
	
private:
	void					handleRealTimeInput();
	
private:
	// Components
	PhysicState				mPhysics;
	sf::FloatRect			mBounds;
	float					mSpeed;
};

#endif // XGS_EXAMPLEPLAYERENTITY_HPP
