#pragma once

#include "Component.hpp"

#include <vector>

namespace gr::gui
{

class Container : public Component
{
public:
    using UPtr = std::unique_ptr<Container>;

public:
    Container(Container&&) noexcept;
    Container& operator=(Container&&) noexcept;

public:
    Container() = default;

    void handleEvent(const sf::Event&) override;

    bool isSelectable() const override;

    void addComponent(Component::UPtr&&);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    bool hasSelection() const;
    void select(std::size_t index);
    void selectNext();
    void selectPrev();

private:
    std::vector<Component::UPtr> _children;
    int _selectedChildIdx = -1; // `-1` if unselected
};

} // namespace gr::gui
