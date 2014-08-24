// Modified version of SceneNode.hpp from SFML Game Development Book

#ifndef XGS_SCENEGRAPHNODE_HPP
#define XGS_SCENEGRAPHNODE_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

#include <X-GS/Time.hpp>

#include <vector>

namespace xgs {
	
	class SceneGraphNode : public sf::Drawable, private sf::NonCopyable
	{
	// Typedefs and enumerations
	public:
		typedef std::unique_ptr<SceneGraphNode> NodePtr;
	
	// Methods
	public:
								SceneGraphNode();
		virtual					~SceneGraphNode();
		
		void					attachChild(NodePtr child);
		NodePtr					detachChild(const SceneGraphNode& node);
		void					destroy();
				
		void					update(const HiResDuration& dt);
		void					draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void					handleEvent(const sf::Event& event);

		sf::Vector2f			getWorldPosition() const;
		sf::Transform			getWorldTransform() const;

	private:
		virtual void			updateThis(const HiResDuration& dt);
		void					updateChildren(const HiResDuration& dt);

		virtual void			handleEventThis(const sf::Event& event);
		void					handleEventChildren(const sf::Event& event);
		
		virtual void			drawThis(sf::RenderTarget& target, sf::RenderStates states) const;
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	// Variables (member / properties)
	public:
		sf::Transformable		mTransformable;

	private:
		std::vector<NodePtr>	mChildren;
		SceneGraphNode*			mParent;
	};
    
} // namespace xgs

#endif // XGS_SCENEGRAPHNODE_HPP
