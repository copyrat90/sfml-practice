#include "SpriteNode.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace gr
{

SpriteNode::SpriteNode(const sf::Texture& texture) : _sprite(texture)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect) : _sprite(texture, rect)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

} // namespace gr
