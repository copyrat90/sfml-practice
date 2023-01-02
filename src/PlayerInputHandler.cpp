#include "PlayerInputHandler.hpp"

#include <SFML/Window/Event.hpp>

#include <cassert>

#include "Aircraft.hpp"
#include "CommandQueue.hpp"

namespace gr
{

namespace
{

struct AircraftAccel
{
    float x, y;

    AircraftAccel(float x, float y) : x(x), y(y)
    {
    }

    void operator()(Aircraft& aircraft, sf::Time) const
    {
        aircraft.accelerate(x, y);
    }
};

} // namespace

PlayerInputHandler::PlayerInputHandler()
{
    _keyBindings.reserve(sf::Keyboard::Key::KeyCount);
    _actionBindings.reserve(Action::TOTAL_COUNT);

    initKeyBindings();
    initActionBindings();
}

void PlayerInputHandler::handleEvent(sf::Event& event, CommandQueue& commandQueue)
{
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        auto keyBind = _keyBindings.find(event.key.code);
        if (keyBind != _keyBindings.end() && !isRealTimeAction(keyBind->second))
            commandQueue.push(_actionBindings[keyBind->second]);
    }
}

void PlayerInputHandler::handleRealTimeInput(CommandQueue& commandQueue)
{
    for (auto [key, action] : _keyBindings)
    {
        if (isRealTimeAction(action) && sf::Keyboard::isKeyPressed(key))
            commandQueue.push(_actionBindings[action]);
    }
}

void PlayerInputHandler::bindKey(sf::Keyboard::Key key, Action action)
{
    // `action`으로 바인딩된 모든 키를 먼저 제거
    for (auto it = _keyBindings.begin(); it != _keyBindings.end();)
    {
        if (it->second == action)
            it = _keyBindings.erase(it);
        else
            ++it;
    }

    _keyBindings[key] = action;
}

auto PlayerInputHandler::getBoundKey(Action action) const -> sf::Keyboard::Key
{
    for (auto [key, boundAction] : _keyBindings)
    {
        if (boundAction == action)
            return key;
    }
    return sf::Keyboard::Key::Unknown;
}

void PlayerInputHandler::initKeyBindings()
{
    // Default keybindings
    using Key = sf::Keyboard::Key;
    _keyBindings[Key::Up] = Action::MOVE_UP;
    _keyBindings[Key::Down] = Action::MOVE_DOWN;
    _keyBindings[Key::Left] = Action::MOVE_LEFT;
    _keyBindings[Key::Right] = Action::MOVE_RIGHT;
}

void PlayerInputHandler::initActionBindings()
{
    constexpr float PLAYER_SPEED = 200.f;

    _actionBindings[Action::MOVE_UP].action = derivedAction<Aircraft>(AircraftAccel(0.f, -PLAYER_SPEED));
    _actionBindings[Action::MOVE_DOWN].action = derivedAction<Aircraft>(AircraftAccel(0.f, PLAYER_SPEED));
    _actionBindings[Action::MOVE_LEFT].action = derivedAction<Aircraft>(AircraftAccel(-PLAYER_SPEED, 0.f));
    _actionBindings[Action::MOVE_RIGHT].action = derivedAction<Aircraft>(AircraftAccel(PLAYER_SPEED, 0.f));

    for (auto& [action, command] : _actionBindings)
        command.categories = NodeCategories::PLAYER_AIRCRAFT;
}

bool PlayerInputHandler::isRealTimeAction(Action action)
{
    switch (action)
    {
    case Action::MOVE_UP:
    case Action::MOVE_DOWN:
    case Action::MOVE_LEFT:
    case Action::MOVE_RIGHT:
        return true;
    default:
        break;
    }
    return false;
}

} // namespace gr
