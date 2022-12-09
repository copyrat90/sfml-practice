#include "Player.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace gr
{

static constexpr int ANIMATION_FRAMES = 6;
static const sf::Time ANIMATION_TIME = sf::milliseconds(160);

static constexpr int SPRITE_WIDTH = 34;
static constexpr int SPRITE_HEIGHT = 32;

Player::Player()
{
    _sprite.setTextureRect({0, 0, SPRITE_WIDTH, SPRITE_HEIGHT});
}

void Player::update(const sf::Time deltaTime)
{
    // sprite 애니메이션 업데이트
    _timeSinceLastAnimUpdate += deltaTime;
    if (_timeSinceLastAnimUpdate >= ANIMATION_TIME)
    {
        _timeSinceLastAnimUpdate -= ANIMATION_TIME;

        auto rect = _sprite.getTextureRect();
        rect.top = (rect.top + SPRITE_HEIGHT) % (ANIMATION_FRAMES * SPRITE_HEIGHT);
        _sprite.setTextureRect(rect);
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Player의 transform을 적용해 위치 이동
    states.transform *= getTransform();
    target.draw(_sprite, states);
}

void Player::setTexture(sf::Texture& texture)
{
    _sprite.setTexture(texture, false);
}

} // namespace gr
