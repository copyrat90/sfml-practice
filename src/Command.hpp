#pragma once

#include <SFML/System/Time.hpp>

#include <cassert>
#include <functional>
#include <type_traits>

#include "NodeCategories.hpp"

namespace gr
{

class SceneNode;

// Command 패턴(함수형)
struct Command
{
    std::function<void(SceneNode&, sf::Time)> action;
    NodeCategories categories = NodeCategories::NONE;
};

// 템플릿과 고차 함수를 이용한 Adapter 함수.
// void(GameObj&, sf::Time) => void(SceneNode&, sf::Time)으로 바꿔서
// Command::action에 담을 수 있도록 한다.
template <typename GameObj, typename Func>
    requires std::is_base_of_v<SceneNode, GameObj>
auto derivedAction(Func func) -> std::function<void(SceneNode&, sf::Time)>
{
    return [func](SceneNode& node, sf::Time deltaTime) {
        // 디버그 모드에서는 dynamic_cast로 캐스팅 가능한지 여부 확인 (디버깅용)
        // 릴리스 모드에서는 assert 제거되어 성능 문제 없음.
        assert(dynamic_cast<GameObj*>(&node) != nullptr);

        GameObj& gameObj = static_cast<GameObj&>(node);
        func(gameObj, deltaTime);
    };
}

} // namespace gr
