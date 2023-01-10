#include "GameState.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <algorithm>
#include <string>

namespace gr
{

GameState::GameState(StateStack& stateStack, Context context)
    : State(stateStack, context), _world(context.window), _playerInputHandler(context.playerInputHandler)
{
}

bool GameState::handleEvent(const sf::Event& event)
{
    // 사용자 입력 처리 (GameState::update() 첫줄과 동일)
    _playerInputHandler.handleEvent(event, _world.getCommandQueue());

    // ESC 눌러서 "일시정지" 상태를 스택에 쌓는다.
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStateStackPush(StateId::PAUSE);

    return true;
}

bool GameState::update(const sf::Time deltaTime)
{
    // 1. 사용자 입력 -> Command로 만들어 Command 큐에 넣기
    // (우선 Command를 처리하지는 않고, 쌓아만 둔다. 처리는 _world.update()에서 수행)
    _playerInputHandler.handleRealTimeInput(_world.getCommandQueue());

    _world.update(deltaTime);

    return true;
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_world);
}

} // namespace gr
