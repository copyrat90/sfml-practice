#include "Component.hpp"

#include <stdexcept>

namespace gr::gui
{

Component::~Component() = default;

bool Component::isSelected() const
{
    return _isSelected;
}

void Component::select()
{
    if (!isSelectable())
        throw std::runtime_error("Component::select() called for non-selectable");

    _isSelected = true;
}

void Component::deselect()
{
    _isSelected = false;
}

bool Component::isActive() const
{
    return _isActive;
}

void Component::activate()
{
    if (!isSelectable())
        throw std::runtime_error("Component::activate() called for non-selectable");

    _isActive = true;
}

void Component::deactivate()
{
    _isActive = false;
}

} // namespace gr::gui
