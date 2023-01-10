#pragma once

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

namespace gr
{

class MenuState final : public State
{
public:
    MenuState(StateStack&, Context);

    bool handleEvent(const sf::Event&) override;
    bool update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    void updateOptionText();

private:
    enum MenuOption
    {
        PLAY,
        EXIT,

        TOTAL_COUNT
    };

private:
    sf::Sprite _bgSprite;
    std::array<sf::Text, MenuOption::TOTAL_COUNT> _texts;

    MenuOption _cursorOption;
};

} // namespace gr
