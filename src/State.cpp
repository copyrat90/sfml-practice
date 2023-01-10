#include "State.hpp"

#include "StateStack.hpp"

namespace gr
{

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,
                        PlayerInputHandler& playerInputHandler)
    : window(window), textures(textures), fonts(fonts), playerInputHandler(playerInputHandler)
{
}

State::State(StateStack& stateStack, Context context) : _stateStack(stateStack), _context(context)
{
}

auto State::getContext() const -> Context
{
    return _context;
}

void State::requestStateStackPush(StateId stateId)
{
    _stateStack.pushState(stateId);
}

void State::requestStateStackPop()
{
    _stateStack.popState();
}

void State::requestStateStackClear()
{
    _stateStack.clearStates();
}

} // namespace gr
