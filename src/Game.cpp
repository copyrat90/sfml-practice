#include "Game.hpp"

#include <algorithm>

namespace gr
{

Game::Game() : _window(sf::VideoMode(1280, 720), "SFML Practice")
{
    _window.setFramerateLimit(FPS);

    loadResources();

    // init test sprite
    _testSprite.setTexture(_textureHolder.get(TextureId::SPLASH_RAT), true);
    _testSprite.setPosition(100, 100);
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

void Game::loadResources()
{
    _textureHolder.loadFromFile(TextureId::SPLASH_RAT, "assets/graphics/splash_rat.png");
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
}

void Game::render()
{
    _window.clear();

    _window.draw(_testSprite);

    _window.display();
}

} // namespace gr
