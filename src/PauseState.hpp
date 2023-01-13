#pragma once

#include "State.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "gui/Container.hpp"

namespace gr
{

class PauseState final : public State
{
public:
    PauseState(StateStack&, Context);

    bool handleEvent(const sf::Event&) override;
    bool update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::RectangleShape _darkRect;
    sf::Text _pauseText;

    gui::Container _guiContainer;
};

} // namespace gr
