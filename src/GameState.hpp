#pragma once

#include "State.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "PlayerInputHandler.hpp"
#include "World.hpp"

namespace gr
{

class GameState final : public State
{
public:
    GameState(StateStack&, Context);

public:
    bool handleEvent(const sf::Event&) override;
    bool update(const sf::Time deltaTime) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    World _world;
    PlayerInputHandler& _playerInputHandler;
};

} // namespace gr
