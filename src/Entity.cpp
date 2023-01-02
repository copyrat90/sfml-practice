#include "Entity.hpp"

namespace gr
{

void Entity::setVelocity(float x, float y)
{
    _velocity = {x, y};
}

void Entity::setVelocity(const sf::Vector2f& velocity)
{
    _velocity = velocity;
}

auto Entity::getVelocity() const -> const sf::Vector2f&
{
    return _velocity;
}

void Entity::accelerate(float x, float y)
{
    setVelocity(getVelocity() + sf::Vector2f{x, y});
}

void Entity::accelerate(const sf::Vector2f& velocity)
{
    setVelocity(getVelocity() + velocity);
}

void Entity::updateCurrent(sf::Time deltaTime)
{
    move(_velocity * deltaTime.asSeconds());
}

} // namespace gr
