// Modified version of SceneNode.cpp from SFML Game Development Book

#include <X-GS/SceneGraphNode.hpp>

#include <cassert>

namespace xgs {
	
	SceneGraphNode::SceneGraphNode()
	: mChildren()
	, mParent(nullptr)
	, mTransformable()
	{
		// Load resources here (RAII)
	}
	
	void SceneGraphNode::attachChild(NodePtr child)
	{
		child->mParent = this;
		mChildren.push_back(std::move(child));
	}
	
	SceneGraphNode::NodePtr SceneGraphNode::detachChild(const SceneGraphNode& node)
	{
		auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (NodePtr& p) { return p.get() == &node; });
		assert(found != mChildren.end());
		
		NodePtr result = std::move(*found);
		result->mParent = nullptr;
		mChildren.erase(found);
		return result;
	}
	
	void SceneGraphNode::destroy()
	{
		assert(mParent && "Attempted to destroy the root scene graph node!");
		mParent->mChildren.clear();
	}
	
	void SceneGraphNode::update(const HiResDuration& dt)
	{
		updateThis(dt);
		updateChildren(dt);
	}
	
	void SceneGraphNode::updateThis(const HiResDuration& dt)
	{
		// Do nothing by default. Implement it on a custom Entity
	}
	
	void SceneGraphNode::updateChildren(const HiResDuration& dt)
	{
		for(NodePtr& child : mChildren)
			child->update(dt);
	}
	
	void SceneGraphNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// Apply transform of current node
		states.transform *= mTransformable.getTransform();
		
		// Draw node and children with changed transform
		drawThis(target, states);
		drawChildren(target, states);
	}
	
	void SceneGraphNode::drawThis(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// Do nothing by default. Implement it on a custom Entity
	}
	
	void SceneGraphNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(const NodePtr& child : mChildren)
			child->draw(target, states);
	}
	
	void SceneGraphNode::handleEvent(const sf::Event &event)
	{
		handleEventThis(event);
		handleEventChildren(event);
	}
	
	void SceneGraphNode::handleEventThis(const sf::Event &event)
	{
		// Do nothing by default. Implement it on a custom Entity
	}
	
	void SceneGraphNode::handleEventChildren(const sf::Event &event)
	{
		for(const NodePtr& child : mChildren)
			child->handleEvent(event);
	}
	
	sf::Vector2f SceneGraphNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}
	
	sf::Transform SceneGraphNode::getWorldTransform() const
	{
		sf::Transform worldTransform = sf::Transform::Identity;
		
		for (const SceneGraphNode* node = this; node != nullptr; node = node->mParent)
			worldTransform = node->mTransformable.getTransform() * worldTransform;
		
		return worldTransform;
	}
	
	SceneGraphNode::~SceneGraphNode()
	{
		// Cleanup
		mParent = nullptr;
	}
	
} // namespace xgs
