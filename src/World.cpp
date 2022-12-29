#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

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

void World::update(sf::Time deltaTime)
{
    _view.move(0, _scrollSpeed * deltaTime.asSeconds());

    auto playerPos = _playerAircraft->getPosition();
    auto playerVelocity = _playerAircraft->getVelocity();

    if (playerPos.x <= _worldBounds.left + 150.f || playerPos.x >= _worldBounds.left + _worldBounds.width - 150.f)
    {
        playerVelocity.x = -playerVelocity.x;
        _playerAircraft->setVelocity(playerVelocity);
    }

    _sceneTree.update(deltaTime);
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
    playerAircraft->setVelocity(40.f, _scrollSpeed);
    _playerAircraft = playerAircraft.get();
    _sceneLayers[Layer::AIR]->addChild(std::move(playerAircraft));

    // Add 2 escorting aircrafts
    auto leftEscort = std::make_unique<Aircraft>(Aircraft::Type::RAPTOR, _textures);
    auto rightEscort = std::make_unique<Aircraft>(Aircraft::Type::RAPTOR, _textures);
    leftEscort->setPosition(-80.f, 50.f);
    rightEscort->setPosition(80.f, 50.f);
    _playerAircraft->addChild(std::move(leftEscort));
    _playerAircraft->addChild(std::move(rightEscort));
}

} // namespace gr
