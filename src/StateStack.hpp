#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include <array>
#include <functional>
#include <memory>
#include <type_traits>
#include <vector>

#include "State.hpp"

namespace gr
{

class StateStack final : public sf::Drawable
{
public:
    StateStack(const StateStack&) = delete;
    StateStack& operator=(const StateStack&) = delete;

public:
    explicit StateStack(State::Context);

    template <typename TState>
        requires std::is_base_of_v<State, TState>
    void registerState(StateId);

    void handleEvent(const sf::Event&);
    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void pushState(StateId);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    auto createState(StateId) -> State::UPtr;
    void applyPendingChanges();

private:
    struct PendingChange
    {
        enum class Type
        {
            PUSH,
            POP,
            CLEAR
        };

        explicit PendingChange(Type, StateId = StateId::NONE);

        Type type;
        StateId stateId;
    };

private:
    std::vector<State::UPtr> _stack;
    std::vector<PendingChange> _pendingChanges;

    State::Context _context;
    std::array<std::function<State::UPtr()>, (int)StateId::TOTAL_COUNT> _stateFactories;
};

template <typename TState>
    requires std::is_base_of_v<State, TState>
void StateStack::registerState(StateId stateId)
{
    _stateFactories[(int)stateId] = [this]() -> State::UPtr { return std::make_unique<TState>(*this, _context); };
}

} // namespace gr
