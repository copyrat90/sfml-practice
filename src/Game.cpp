#include "Game.hpp"

#include <SFML/Window/Event.hpp>

#include <algorithm>
#include <string>

namespace gr
{

Game::Game()
    : _window(sf::VideoMode(640, 480), "SFML Practice"), _world(_window), _statsFrameCounter(0),
      _statsElapsedSeconds(sf::seconds(0))
{
    _window.setFramerateLimit(FPS);
    _font.loadFromFile("assets/fonts/Sansation.ttf");
    _statsText.setFont(_font);
    _statsText.setPosition(5.f, 5.f);
    _statsText.setCharacterSize(10);
}

void Game::run()
{
    const sf::Time FIXED_DELTA_TIME = sf::seconds(SEC_PER_FRAME);
    const sf::Time MAX_REMAIN_TIME = sf::seconds(0.25f);

    sf::Clock frameTimer;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (_window.isOpen())
    {
        sf::Time elapsedTime = frameTimer.restart();
        timeSinceLastUpdate += elapsedTime;
        timeSinceLastUpdate = std::min(timeSinceLastUpdate, MAX_REMAIN_TIME);

        while (timeSinceLastUpdate >= FIXED_DELTA_TIME)
        {
            timeSinceLastUpdate -= FIXED_DELTA_TIME;

            processEvents();
            update(FIXED_DELTA_TIME);
        }
        updateStatistics(elapsedTime);
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
            _playerInputHandler.handleEvent(event, _world.getCommandQueue());
            break;
        }
    }

    // 1. 사용자 입력 -> Command로 만들어 Command 큐에 넣기
    // (우선 Command를 처리하지는 않고, 쌓아만 둔다. 처리는 update()에서 수행)
    _playerInputHandler.handleRealTimeInput(_world.getCommandQueue());
}

void Game::update(const sf::Time deltaTime)
{
    _world.update(deltaTime);
}

void Game::render()
{
    _window.clear();

    _window.draw(_world);

    _window.setView(_window.getDefaultView());
    _window.draw(_statsText);

    _window.display();
}

void Game::updateStatistics(const sf::Time deltaTime)
{
    ++_statsFrameCounter;
    _statsElapsedSeconds += deltaTime;
    if (_statsElapsedSeconds > sf::seconds(1))
    {
        _statsText.setString("FPS : " + std::to_string(_statsFrameCounter) +
                             "\n"
                             "Time / Update : " +
                             std::to_string(_statsElapsedSeconds.asMicroseconds() / _statsFrameCounter) + "us");

        _statsFrameCounter = 0;
        _statsElapsedSeconds -= sf::seconds(1);
    }
}

} // namespace gr
