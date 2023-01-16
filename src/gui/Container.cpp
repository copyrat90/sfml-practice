#include "Container.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <stdexcept>
#include <string>

namespace gr::gui
{

Container::Container(Container&& other) noexcept
    : Component(std::move(other)), _children(std::move(other._children)), _selectedChildIdx(other._selectedChildIdx)
{
}

Container& Container::operator=(Container&& other) noexcept
{
    Component::operator=(std::move(other));
    _children = std::move(other._children);
    _selectedChildIdx = other._selectedChildIdx;

    return *this;
}

void Container::handleEvent(const sf::Event& event)
{
    // 버튼이 활성화된 경우(e.g. 바인딩 대기중), 이벤트를 해당 버튼에 전달
    // 이 방식으로는 ON/OFF 스위치 만드려면 별도의 isOn() 이 필요할듯하다.
    if (hasSelection() && _children[_selectedChildIdx]->isActive())
    {
        _children[_selectedChildIdx]->handleEvent(event);
    }
    // 아니면 위/아래 이동 처리
    else if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            using Key = sf::Keyboard::Key;
        case Key::Up:
        case Key::W:
            selectPrev();
            break;
        case Key::Down:
        case Key::S:
            selectNext();
            break;
        case Key::Enter:
        case Key::Space:
            if (hasSelection())
                _children[_selectedChildIdx]->activate();
            break;
        default:
            break;
        }
    }
}

bool Container::isSelectable() const
{
    return false;
}

void Container::addComponent(Component::UPtr&& component)
{
    _children.push_back(std::move(component));

    auto& addedComponent = _children.back();
    if (!hasSelection() && addedComponent->isSelectable())
        select(_children.size() - 1);
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (const auto& child : _children)
        target.draw(*child, states);
}

bool Container::hasSelection() const
{
    return _selectedChildIdx >= 0;
}

void Container::select(std::size_t index)
{
    if (index >= _children.size())
        throw std::runtime_error("index=" + std::to_string(index) + " out of bound");

    if (_children[index]->isSelectable())
    {
        if (hasSelection())
            _children[_selectedChildIdx]->deselect();

        _children[index]->select();
        _selectedChildIdx = index;
    }
}

void Container::selectNext()
{
    if (!hasSelection())
        return;

    int nextSelectIdx = _selectedChildIdx;
    do
        nextSelectIdx = (nextSelectIdx + 1) % _children.size();
    while (!_children[nextSelectIdx]->isSelectable());

    select(nextSelectIdx);
}

void Container::selectPrev()
{
    if (!hasSelection())
        return;

    int prevSelectIdx = _selectedChildIdx;
    do
        prevSelectIdx = (prevSelectIdx - 1 + _children.size()) % _children.size();
    while (!_children[prevSelectIdx]->isSelectable());

    select(prevSelectIdx);
}

} // namespace gr::gui
