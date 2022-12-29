#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "World.hpp"

namespace gr
{

class Game final
{
public:
    static constexpr int FPS = 60;
    static constexpr float SEC_PER_FRAME = 1.f / FPS;

public:
    Game();

    void run();

private:
    void processEvents();
    void update(const sf::Time deltaTime);
    void render();

private:
    sf::RenderWindow _window;
    World _world;
};

} // namespace gr
