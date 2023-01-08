#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "PlayerInputHandler.hpp"
#include "ResourceHolder.hpp"
#include "ResourceId.hpp"
#include "StateStack.hpp"

namespace gr
{

class App final
{
public:
    static constexpr int FPS = 60;
    static constexpr float SEC_PER_FRAME = 1.f / FPS;

    App(const App&) = delete;
    App& operator=(const App&) = delete;

public:
    App();

    void run();

private:
    void processEvents();
    void update(const sf::Time deltaTime);
    void render();

    void updateStatistics(const sf::Time deltaTime);

    void registerStates();

private:
    sf::RenderWindow _window;
    TextureHolder _textures;
    FontHolder _fonts;

    PlayerInputHandler _playerInputHandler;
    StateStack _stateStack;

    // for statistics
    int _statsFrameCounter;
    sf::Time _statsElapsedSeconds;
    sf::Text _statsText;
};

} // namespace gr
