#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceHolder.hpp"
#include "ResourceId.hpp"

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
    void loadResources();

    void processEvents();
    void update(const sf::Time deltaTime);
    void render();

private:
    sf::RenderWindow _window;

    TextureHolder _textureHolder;

    sf::Sprite _testSprite;
};

} // namespace gr
