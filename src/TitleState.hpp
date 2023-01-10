#pragma once

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace gr
{

class TitleState final : public State
{
public:
    TitleState(StateStack&, Context);

    bool handleEvent(const sf::Event&) override;
    bool update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::Sprite _bgSprite;

    sf::Text _text;
    sf::Time _textFlickerTimer;
    bool _isTextVisible;
};

} // namespace gr
