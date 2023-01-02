#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>

#include <memory>
#include <vector>

#include "NodeCategories.hpp"

namespace gr
{

struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable
{
public:
    using UPtr = std::unique_ptr<SceneNode>;

    SceneNode(const SceneNode&) = delete;
    SceneNode& operator=(const SceneNode&) = delete;

public:
    SceneNode();

    void addChild(UPtr node);
    UPtr removeChild(const SceneNode& child);

    void update(sf::Time deltaTime);

    auto getWorldPosition() const -> sf::Vector2f;
    auto getWorldTransform() const -> sf::Transform;

    virtual auto getCategories() const -> NodeCategories;
    void onCommand(const Command&, sf::Time deltaTime);

private:
    void updateChildren(sf::Time deltaTime);
    virtual void updateCurrent(sf::Time deltaTime);

    void draw(sf::RenderTarget&, sf::RenderStates) const final;
    void drawChildren(sf::RenderTarget&, sf::RenderStates) const;
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

private:
    SceneNode* _parent;
    std::vector<UPtr> _children;
};

} // namespace gr
