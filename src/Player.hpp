#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

namespace gr
{

class Player final : public sf::Drawable, public sf::Transformable
{
public:
    Player();

    void update(const sf::Time deltaTime);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void setTexture(sf::Texture&);

private:
    sf::Sprite _sprite;
    sf::Time _timeSinceLastAnimUpdate;
};

} // namespace gr
