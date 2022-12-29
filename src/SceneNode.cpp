#include "SceneNode.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cassert>

namespace gr
{

SceneNode::SceneNode() : _parent(nullptr)
{
}

void SceneNode::addChild(UPtr node)
{
    node->_parent = this;
    _children.push_back(std::move(node));
}

auto SceneNode::removeChild(const SceneNode& child) -> UPtr
{
    auto it =
        std::find_if(_children.begin(), _children.end(), [&child](const UPtr& ptr) { return ptr.get() == &child; });
    assert(it != _children.end());

    UPtr result = std::move(*it);
    result->_parent = nullptr;
    _children.erase(it);
    return result;
}

void SceneNode::update(sf::Time deltaTime)
{
    updateCurrent(deltaTime);
    updateChildren(deltaTime);
}

auto SceneNode::getWorldPosition() const -> sf::Vector2f
{
    return getWorldTransform() * sf::Vector2f(0, 0);
}

auto SceneNode::getWorldTransform() const -> sf::Transform
{
    sf::Transform worldTransform = getTransform();
    for (auto p = _parent; p != nullptr; p = p->_parent)
        worldTransform = p->getTransform() * worldTransform;

    return worldTransform;
}

void SceneNode::updateChildren(sf::Time deltaTime)
{
    for (auto& child : _children)
        child->update(deltaTime);
}

void SceneNode::updateCurrent(sf::Time deltaTime)
{
    // Do nothing by default.
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& child : _children)
        target.draw(*child, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
    // Do nothing by default.
}

} // namespace gr
