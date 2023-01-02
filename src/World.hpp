#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>

#include <array>

#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "ResourceId.hpp"
#include "SceneNode.hpp"

namespace sf
{
class RenderWindow;
}

namespace gr
{

class Aircraft;

class World final : public sf::Drawable
{
public:
    World(const World&) = delete;
    World& operator=(const World&) = delete;

public:
    World(sf::RenderWindow&);

    auto getCommandQueue() -> CommandQueue&;

    void update(sf::Time deltaTime);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void loadTextures();
    void buildScene();

    // 대각선 속도도 1방향 속도와 동일하게 정규화
    void normalizePlayerVelocity();
    // 위치를 화면 내로 고정시킴
    void normalizePlayerPosition();

private:
    enum Layer
    {
        BG,
        AIR,
        TOTAL_COUNT
    };

private:
    TextureHolder _textures;

    const sf::FloatRect _worldBounds;
    const sf::Vector2f _spawnPos;

    SceneNode _sceneTree;
    std::array<SceneNode*, (int)Layer::TOTAL_COUNT> _sceneLayers;

    CommandQueue _commandQueue;

    sf::View _view;
    float _scrollSpeed;
    Aircraft* _playerAircraft;
};

} // namespace gr
