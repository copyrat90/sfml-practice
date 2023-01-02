#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <cmath>

#include "Aircraft.hpp"
#include "SpriteNode.hpp"

namespace gr
{

World::World(sf::RenderWindow& window)
    : _worldBounds(0, 0, window.getSize().x, 2000),
      _spawnPos(window.getSize().x / 2.f, _worldBounds.height - window.getSize().y / 2.f),
      _view(window.getDefaultView()), _scrollSpeed(-50.f), _playerAircraft(nullptr)
{
    loadTextures();
    buildScene();

    _view.setCenter(_spawnPos);
}

auto World::getCommandQueue() -> CommandQueue&
{
    return _commandQueue;
}

void World::update(sf::Time deltaTime)
{
    _view.move(0, _scrollSpeed * deltaTime.asSeconds());

    _playerAircraft->setVelocity(0, 0);
    // 2. 큐에서 Command 를 꺼내서, 트리 내 필요한 모든 노드에 대해 Command 실행
    // (플레이어 기체 가속 Command도 실행될 것.)
    while (!_commandQueue.isEmpty())
        _sceneTree.onCommand(_commandQueue.pop(), deltaTime);

    normalizePlayerVelocity();
    // 플레이어 기체 스크롤 속도 추가
    _playerAircraft->accelerate(0, _scrollSpeed);

    // 3. 모든 노드에 대해 update 실행(플레이어 기체 위치가, 위에서 계산된 속도에 맞게 변경)
    _sceneTree.update(deltaTime);

    normalizePlayerPosition();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(_view);

    target.draw(_sceneTree, states);
}

void World::loadTextures()
{
    _textures.loadFromFile(TextureId::DESERT, "assets/graphics/Desert.png");
    _textures.loadFromFile(TextureId::EAGLE, "assets/graphics/Eagle.png");
    _textures.loadFromFile(TextureId::RAPTOR, "assets/graphics/Raptor.png");
}

void World::buildScene()
{
    for (int i = 0; i < Layer::TOTAL_COUNT; ++i)
    {
        auto layer = std::make_unique<SceneNode>();
        _sceneLayers[i] = layer.get();
        _sceneTree.addChild(std::move(layer));
    }

    // Add desert bg
    auto& desertTexture = _textures.get(TextureId::DESERT);
    desertTexture.setRepeated(true);
    auto desertBg = std::make_unique<SpriteNode>(desertTexture, sf::IntRect(_worldBounds));
    _sceneLayers[Layer::BG]->addChild(std::move(desertBg));

    // Add player aircraft
    auto playerAircraft = std::make_unique<Aircraft>(Aircraft::Type::EAGLE, _textures);
    playerAircraft->setPosition(_spawnPos);
    _playerAircraft = playerAircraft.get();
    _sceneLayers[Layer::AIR]->addChild(std::move(playerAircraft));
}

void World::normalizePlayerVelocity()
{
    auto velocity = _playerAircraft->getVelocity();
    if (velocity.x != 0 && velocity.y != 0)
    {
        velocity /= std::sqrt(2.f);
        _playerAircraft->setVelocity(velocity);
    }
}

void World::normalizePlayerPosition()
{
    constexpr float PADDING = 40.f;
    const sf::FloatRect viewBounds(_view.getCenter() - _view.getSize() / 2.f, _view.getSize());

    auto [x, y] = _playerAircraft->getPosition();

    x = std::min(x, viewBounds.left + viewBounds.width - PADDING);
    x = std::max(x, viewBounds.left + PADDING);
    y = std::min(y, viewBounds.top + viewBounds.height - PADDING);
    y = std::max(y, viewBounds.top + PADDING);

    _playerAircraft->setPosition(x, y);
}

} // namespace gr
