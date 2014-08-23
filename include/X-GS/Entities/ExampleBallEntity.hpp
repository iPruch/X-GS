#ifndef XGS_EXAMPLEBALLENTITY_HPP
#define XGS_EXAMPLEBALLENTITY_HPP

#include <SFML/Graphics/RenderTarget.hpp> // Completes the RenderTarget forward declaration in Drawable, inherited from Entity <- SceneGrahpNode
#include <SFML/Graphics/CircleShape.hpp>

#include <X-GS/Entity.hpp>
#include <X-GS/PhysicState.hpp>
#include <X-GS/Integrator.hpp>

using namespace xgs;

	/*
	 Derived class
	 */
	class ExampleBallEntity : public Entity
	{
	public:
								ExampleBallEntity(sf::FloatRect bounds);
		virtual					~ExampleBallEntity();
		
		virtual void			updateThis(const HiResDuration& dt);
		virtual void			drawThis(sf::RenderTarget& target, sf::RenderStates states) const;
		
		void					setBounds(sf::FloatRect bounds);
				
	private:
		// Components
		sf::CircleShape			mCircle;
		PhysicState				mPhysics;
		sf::FloatRect			mBounds;

	};

#endif // XGS_EXAMPLEBALLENTITY_HPP
