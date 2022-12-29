#pragma once

#include "SceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace gr
{

class SpriteNode : public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture&);
    SpriteNode(const sf::Texture&, const sf::IntRect& rect);

private:
    void drawCurrent(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::Sprite _sprite;
};

} // namespace gr
