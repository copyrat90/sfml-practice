#include "App.hpp"

#include <SFML/Window/Event.hpp>

#include <algorithm>
#include <string>

#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "TitleState.hpp"

namespace gr
{

App::App()
    : _window(sf::VideoMode(640, 480), "SFML Practice"),
      _stateStack(State::Context(_window, _textures, _fonts, _playerInputHandler)), _statsFrameCounter(0),
      _statsElapsedSeconds(sf::seconds(0))
{
    _window.setFramerateLimit(FPS);
    _window.setKeyRepeatEnabled(false);

    _fonts.loadFromFile(FontId::SANSATION, "assets/fonts/Sansation.ttf");
    _textures.loadFromFile(TextureId::TITLE_SCREEN, "assets/graphics/TitleScreen.png");
    _textures.loadFromFile(TextureId::BUTTON_NORMAL, "assets/graphics/ButtonNormal.png");
    _textures.loadFromFile(TextureId::BUTTON_SELECTED, "assets/graphics/ButtonSelected.png");
    _textures.loadFromFile(TextureId::BUTTON_PRESSED, "assets/graphics/ButtonPressed.png");

    _statsText.setFont(_fonts.get(FontId::SANSATION));
    _statsText.setPosition(5.f, 5.f);
    _statsText.setCharacterSize(10);

    registerStates();
    _stateStack.pushState(StateId::TITLE);
}

void App::run()
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

            // 상태 스택이 비었으면, 게임 종료
            if (_stateStack.isEmpty())
                _window.close();
        }
        updateStatistics(elapsedTime);
        render();
    }
}

void App::processEvents()
{
    for (auto event = sf::Event{}; _window.pollEvent(event);)
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            _window.close();
            break;
        default:
            _stateStack.handleEvent(event);
            break;
        }
    }
}

void App::update(const sf::Time deltaTime)
{
    _stateStack.update(deltaTime);
}

void App::render()
{
    _window.clear();

    _window.draw(_stateStack);

    _window.setView(_window.getDefaultView());
    _window.draw(_statsText);

    _window.display();
}

void App::updateStatistics(const sf::Time deltaTime)
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

void App::registerStates()
{
    _stateStack.registerState<TitleState>(StateId::TITLE);
    _stateStack.registerState<MenuState>(StateId::MENU);
    _stateStack.registerState<GameState>(StateId::GAME);
    _stateStack.registerState<PauseState>(StateId::PAUSE);
}

} // namespace gr
