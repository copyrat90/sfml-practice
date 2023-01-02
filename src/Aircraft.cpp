#include "Aircraft.hpp"

#include <cassert>

#include <SFML/Graphics/RenderTarget.hpp>

#include "ResourceHolder.hpp"

namespace gr
{

static TextureId toTextureId(Aircraft::Type type)
{
    switch (type)
    {
        using Type = Aircraft::Type;
    case Type::EAGLE:
        return TextureId::EAGLE;
    case Type::RAPTOR:
        return TextureId::RAPTOR;
    }
    assert(false);
    return TextureId::EAGLE;
}

Aircraft::Aircraft(Type type, const TextureHolder& textures) : _type(type), _sprite(textures.get(toTextureId(type)))
{
    const sf::FloatRect bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

auto Aircraft::getCategories() const -> NodeCategories
{
    if (_type == Type::EAGLE)
        return NodeCategories::PLAYER_AIRCRAFT;
    return NodeCategories::ENEMY_AIRCRAFT;
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

} // namespace gr
