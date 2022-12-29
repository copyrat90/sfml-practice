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

void Entity::updateCurrent(sf::Time deltaTime)
{
    move(_velocity * deltaTime.asSeconds());
}

} // namespace gr
