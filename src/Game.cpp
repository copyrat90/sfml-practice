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

    if (!sf::Shader::isAvailable())
        throw std::runtime_error("Shaders are not supported on your hardware");

    _loadResources();

    // 각 sprite의 texture 초기화
    _tilemapSprite.setTexture(_textureHolder.get(TextureId::TILEMAP), true);
    _uiSprite.setTexture(_textureHolder.get(TextureId::UI), true);
    _player.setTexture(_textureHolder.get(TextureId::PLAYER));

    // 플레이어 위치 이동 (내부 해상도 426 x 240 기준)
    _player.setPosition(132, 173);

    // First & Second Pass 렌더링할 텍스처 생성
    if (!_postEffectRequired.create(INTERNAL_WIDTH, INTERNAL_HEIGHT) ||
        !_postEffectApplied.create(INTERNAL_WIDTH, INTERNAL_HEIGHT))
        throw std::runtime_error("Render texture creation failed");

    // 셰이더 전역 상수 설정
    auto& heatHazeShader = _shaderHolder.get(ShaderId::HEAT_HAZE);
    heatHazeShader.setUniform("u_postEffectRequired", _postEffectRequired.getTexture());
    heatHazeShader.setUniform("u_internalResolution", sf::Vector2f{INTERNAL_WIDTH, INTERNAL_HEIGHT});
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

    _shaderHolder.loadFromFile(ShaderId::HEAT_HAZE, "assets/shaders/heat_haze.frag", sf::Shader::Type::Fragment);
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
        case sf::Event::KeyPressed:
            _isCustomShaderEnabled = !_isCustomShaderEnabled;
            break;
        default:
            break;
        }
    }
}

void Game::_update(const sf::Time deltaTime)
{
    _player.update(deltaTime);

    // 시간에 따른 떨림 각도 업데이트
    constexpr float PI = 3.1415926f;
    constexpr float WAVE_PER_SECOND = 0.25f * 2 * PI;
    _hazeRadians += WAVE_PER_SECOND * deltaTime.asSeconds();
    while (_hazeRadians >= 2 * PI)
        _hazeRadians -= 2 * PI;
}

void Game::_render()
{
    _renderFirstPass();
    _renderSecondPass();
    _renderToWindowWithScaling();
}

void Game::_renderFirstPass()
{
    _postEffectRequired.clear();

    // 커스텀 셰이더를 적용할 개체들만 그림.
    // UI 는 2nd Pass 에서 셰이더 적용 없이 그릴 예정.
    _postEffectRequired.draw(_tilemapSprite);
    _postEffectRequired.draw(_player);

    _postEffectRequired.display();
}

void Game::_renderSecondPass()
{
    _postEffectApplied.clear();

    // 셰이더의 떨림 각도 전역변수 업데이트
    auto& customFragShader = _shaderHolder.get(ShaderId::HEAT_HAZE);
    customFragShader.setUniform("u_hazeRadians", _hazeRadians);

    // 커스텀 셰이더를 적용하는 `shaderStates`
    auto shaderStates = sf::RenderStates::Default;
    if (_isCustomShaderEnabled)
        shaderStates.shader = &customFragShader;

    sf::Sprite postEffectRequiredSprite(_postEffectRequired.getTexture());

    _postEffectApplied.draw(postEffectRequiredSprite, shaderStates);
    _postEffectApplied.draw(_uiSprite); // UI는 항상 셰이더 미적용

    _postEffectApplied.display();
}

void Game::_renderToWindowWithScaling()
{
    _window.clear();

    // 실제 윈도우 크기에 맞게 업스케일링 해서 그리기
    sf::Sprite finalGameFrame(_postEffectApplied.getTexture());
    finalGameFrame.scale({WINDOW_SCALE_FACTOR, WINDOW_SCALE_FACTOR});

    _window.draw(finalGameFrame);

    _window.display();
}

} // namespace gr
