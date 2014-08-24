// Modified version of SceneNode.hpp from SFML-Game-Development-Book

#ifndef XGS_ENTITY_HPP
#define XGS_ENTITY_HPP

#include <X-GS/SceneGraphNode.hpp>

#include <SFML/Window/Event.hpp>

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
		
		virtual void			updateThis(const HiResDuration& dt) = 0;
		virtual void			drawThis(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		virtual void			handleEventThis(const sf::Event& event) = 0;
		
	// Variables (member / properties)
	private:
		// TODO: Identification / messaging
	};
    
} // namespace xgs

#endif // XGS_ENTITY_HPP
