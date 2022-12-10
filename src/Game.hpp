#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceHolder.hpp"
#include "ResourceId.hpp"

#include "Player.hpp"

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
    void _loadResources();

    void _processEvents();
    void _update(const sf::Time deltaTime);
    void _render();

    void _renderFirstPass();
    void _renderSecondPass();
    void _renderToWindowWithScaling();

private:
    sf::RenderWindow _window;
    sf::RenderTexture _postEffectRequired;
    sf::RenderTexture _postEffectApplied;

    TextureHolder _textureHolder;
    ShaderHolder _shaderHolder;

    bool _isCustomShaderEnabled = true;
    float _hazeRadians = 0;

    sf::Sprite _tilemapSprite;
    sf::Sprite _uiSprite;
    Player _player;
};

} // namespace gr
