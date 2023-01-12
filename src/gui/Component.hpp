#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>

namespace sf
{
class Event;
}

namespace gr::gui
{

class Component : public sf::Transformable, public sf::Drawable
{
public:
    // 책에서는 std::shared_ptr 쓰는데, 설명이 부족함.
    // 컴포넌트가 여러 state에서 재사용될 수 있다고는 하는데...
    using UPtr = std::unique_ptr<Component>;

public:
    // 복사 방지
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

    // 이동 허용
    Component(Component&&) noexcept = default;
    Component& operator=(Component&&) noexcept = default;

public:
    virtual ~Component();

    Component() = default;

    virtual void handleEvent(const sf::Event&) = 0;

    virtual bool isSelectable() const = 0;
    bool isSelected() const;
    virtual void select();
    virtual void deselect();

    bool isActive() const;
    virtual void activate();
    virtual void deactivate();

private:
    bool _isSelected = false;
    bool _isActive = false;
};

} // namespace gr::gui
