#include "Label.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "../ResourceHolder.hpp"

namespace gr::gui
{

Label::Label(Label&& other) noexcept : Component(std::move(other)), _text(std::move(other._text))
{
}

Label& Label::operator=(Label&& other) noexcept
{
    Component::operator=(std::move(other));
    _text = std::move(other._text);

    return *this;
}

Label::Label(const std::string& str, const FontHolder& fonts) : _text(str, fonts.get(FontId::SANSATION), 16)
{
}

void Label::handleEvent(const sf::Event& event)
{
}

bool Label::isSelectable() const
{
    return false;
}

void Label::setString(const std::string& str)
{
    _text.setString(str);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_text, states);
}

} // namespace gr::gui
