// Modified version of SceneNode.hpp from SFML-Game-Development-Book

#ifndef XGS_ENTITY_HPP
#define XGS_ENTITY_HPP

#include <X-GS/SceneGraphNode.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp> // Completes the RenderTarget forward declaration in Drawable, inherited from Entity <- SceneGrahpNode

namespace xgs {
	
	/*
	 Abstract class. Look at ExampleEntity.hpp/cpp in Entities folder
	 to see an example of use.
	 */
	class Entity : public SceneGraphNode
	{
		// Methods
	public:
		Entity() {}
		virtual					~Entity() {}
		
		virtual void			updateThis(const HiResDuration& dt) override = 0;
		virtual void			drawThis(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
		virtual void			handleEventThis(const sf::Event& event) override = 0;
		
		// Variables (member / properties)
	private:
		// TODO: Identification / messaging
	};
    
} // namespace xgs

#endif // XGS_ENTITY_HPP
