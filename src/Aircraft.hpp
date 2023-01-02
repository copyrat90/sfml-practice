#pragma once

#include "Entity.hpp"

#include "ResourceId.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace gr
{

class Aircraft final : public Entity
{
public:
    enum class Type
    {
        EAGLE,
        RAPTOR
    };

public:
    Aircraft(Type type, const TextureHolder&);

    auto getCategories() const -> NodeCategories override;

private:
    void drawCurrent(sf::RenderTarget&, sf::RenderStates) const override;

private:
    Type _type;
    sf::Sprite _sprite;
};

} // namespace gr
