#include "StateStack.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <stdexcept>

namespace gr
{

StateStack::StateStack(State::Context context) : _context(context)
{
}

void StateStack::handleEvent(const sf::Event& event)
{
    // 스택의 위->아래 순서로 handleEvent() 호출
    for (auto it = _stack.rbegin(); it != _stack.rend(); ++it)
    {
        // 그 다음 state가 handleInput() 필요 없는 상태면, break
        if (!(*it)->handleEvent(event))
            break;
    }

    applyPendingChanges();
}

void StateStack::update(sf::Time deltaTime)
{
    // 스택의 위->아래 순서로 update() 호출
    for (auto it = _stack.rbegin(); it != _stack.rend(); ++it)
    {
        // 그 다음 state가 update() 필요 없는 상태면, break
        if (!(*it)->update(deltaTime))
            break;
    }

    applyPendingChanges();
}

void StateStack::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // 스택의 아래->위 순서로 draw() 호출
    for (auto& state : _stack)
        target.draw(*state, states);
}

void StateStack::pushState(StateId stateId)
{
    _pendingChanges.push_back(PendingChange(PendingChange::Type::PUSH, stateId));
}

void StateStack::popState()
{
    _pendingChanges.push_back(PendingChange(PendingChange::Type::POP));
}

void StateStack::clearStates()
{
    _pendingChanges.push_back(PendingChange(PendingChange::Type::CLEAR));
}

bool StateStack::isEmpty() const
{
    return _stack.empty();
}

auto StateStack::createState(StateId stateId) -> State::UPtr
{
    if (stateId == StateId::NONE)
        throw std::logic_error("create state requested for StateId::NONE");

    auto& factory = _stateFactories[(int)stateId];
    if (!factory)
        throw std::logic_error("create state requested for unregistered stateId=" + std::to_string((int)stateId));

    return factory();
}

void StateStack::applyPendingChanges()
{
    for (const auto& pendingChange : _pendingChanges)
    {
        switch (pendingChange.type)
        {
            using Type = PendingChange::Type;
        case Type::PUSH:
            _stack.push_back(createState(pendingChange.stateId));
            break;
        case Type::POP:
            if (_stack.empty())
                throw std::logic_error("pop requested for empty state stack");
            _stack.pop_back();
            break;
        case Type::CLEAR:
            _stack.clear();
            break;
        default:
            throw std::logic_error("Invalid pendingChange.type=" + std::to_string((int)pendingChange.type));
        }
    }

    _pendingChanges.clear();
}

StateStack::PendingChange::PendingChange(Type type, StateId stateId) : type(type), stateId(stateId)
{
}

} // namespace gr
