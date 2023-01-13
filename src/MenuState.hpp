#pragma once

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include "gui/Container.hpp"

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
    sf::Sprite _bgSprite;

    gui::Container _guiContainer;
};

} // namespace gr
