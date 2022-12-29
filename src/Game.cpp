#include "Game.hpp"

#include <SFML/Window/Event.hpp>

#include <algorithm>

namespace gr
{

Game::Game() : _window(sf::VideoMode(640, 480), "SFML Practice"), _world(_window)
{
    _window.setFramerateLimit(FPS);
}

void Game::run()
{
    const sf::Time FIXED_DELTA_TIME = sf::seconds(SEC_PER_FRAME);
    const sf::Time MAX_REMAIN_TIME = sf::seconds(0.25f);

    sf::Clock frameTimer;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (_window.isOpen())
    {
        timeSinceLastUpdate += frameTimer.restart();
        timeSinceLastUpdate = std::min(timeSinceLastUpdate, MAX_REMAIN_TIME);

        while (timeSinceLastUpdate >= FIXED_DELTA_TIME)
        {
            timeSinceLastUpdate -= FIXED_DELTA_TIME;

            processEvents();
            update(FIXED_DELTA_TIME);
        }
        render();
    }
}

void Game::processEvents()
{
    for (auto event = sf::Event{}; _window.pollEvent(event);)
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            _window.close();
            break;
        default:
            break;
        }
    }
}

void Game::update(const sf::Time deltaTime)
{
    _world.update(deltaTime);
}

void Game::render()
{
    _window.clear();

    _window.draw(_world);

    _window.display();
}

} // namespace gr
