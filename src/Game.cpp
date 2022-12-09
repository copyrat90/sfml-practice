#include "Game.hpp"

#include <algorithm>

namespace gr
{

// 내부 해상도: 게임 픽셀아트 단위 해상도
static constexpr int INTERNAL_WIDTH = 426;
static constexpr int INTERNAL_HEIGHT = 240;

// 윈도우의 해상도는 내부 해상도 x 3 으로 설정
static constexpr int WINDOW_SCALE_FACTOR = 3;
static constexpr int WINDOW_WIDTH = INTERNAL_WIDTH * WINDOW_SCALE_FACTOR;
static constexpr int WINDOW_HEIGHT = INTERNAL_HEIGHT * WINDOW_SCALE_FACTOR;

Game::Game() : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Heat Haze Shader Example")
{
    _window.setFramerateLimit(FPS);

    _loadResources();

    // 각 sprite의 texture 초기화
    _tilemapSprite.setTexture(_textureHolder.get(TextureId::TILEMAP), true);
    _uiSprite.setTexture(_textureHolder.get(TextureId::UI), true);
    _player.setTexture(_textureHolder.get(TextureId::PLAYER));

    // 플레이어 위치 이동 (내부 해상도 426 x 240 기준)
    _player.setPosition(132, 173);
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

            _processEvents();
            _update(FIXED_DELTA_TIME);
        }
        _render();
    }
}

void Game::_loadResources()
{
    _textureHolder.loadFromFile(TextureId::PLAYER, "assets/graphics/player.png");
    _textureHolder.loadFromFile(TextureId::TILEMAP, "assets/graphics/tilemap.png");
    _textureHolder.loadFromFile(TextureId::UI, "assets/graphics/ui.png");
}

void Game::_processEvents()
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

void Game::_update(const sf::Time deltaTime)
{
    _player.update(deltaTime);
}

void Game::_render()
{
    _window.clear();

    // 실제 윈도우는 3배 크기이므로, 3배 키우는 transform 적용
    auto states = sf::RenderStates::Default;
    states.transform.scale(WINDOW_SCALE_FACTOR, WINDOW_SCALE_FACTOR);

    _window.draw(_tilemapSprite, states);
    _window.draw(_player, states);
    _window.draw(_uiSprite, states);

    _window.display();
}

} // namespace gr
