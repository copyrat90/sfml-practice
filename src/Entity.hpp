#pragma once

#include "SceneNode.hpp"

#include <SFML/System/Vector2.hpp>

namespace gr
{

class Entity : public SceneNode
{
public:
    void setVelocity(float x, float y);
    void setVelocity(const sf::Vector2f& velocity);
    auto getVelocity() const -> const sf::Vector2f&;

    void accelerate(float x, float y);
    void accelerate(const sf::Vector2f& velocity);

private:
    void updateCurrent(sf::Time deltaTime) override;

private:
    sf::Vector2f _velocity;
};

} // namespace gr
