#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

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

    void updateStatistics(const sf::Time deltaTime);

private:
    sf::RenderWindow _window;
    sf::Font _font;

    World _world;

    // for statistics
    int _statsFrameCounter;
    sf::Time _statsElapsedSeconds;
    sf::Text _statsText;
};

} // namespace gr
