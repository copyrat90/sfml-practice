#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <unordered_map>

#include "Command.hpp"

namespace sf
{
class Event;
}

namespace gr
{

class CommandQueue;

// Input events -> Command
class PlayerInputHandler
{
public:
    enum Action
    {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        TOTAL_COUNT
    };

public:
    PlayerInputHandler();

    void handleEvent(sf::Event&, CommandQueue&);
    void handleRealTimeInput(CommandQueue&);

    void bindKey(sf::Keyboard::Key, Action);
    auto getBoundKey(Action) const -> sf::Keyboard::Key;

private:
    void initKeyBindings();
    void initActionBindings();
    static bool isRealTimeAction(Action);

private:
    std::unordered_map<sf::Keyboard::Key, Action> _keyBindings;
    std::unordered_map<Action, Command> _actionBindings;
};

} // namespace gr
