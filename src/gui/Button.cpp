#include "Button.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "../ResourceHolder.hpp"
#include "../Util.hpp"

namespace gr::gui
{

Button::Button(Button&& other) noexcept
    : Component(std::move(other)), _idleTexture(other._idleTexture), _selectedTexture(other._selectedTexture),
      _holdTexture(other._holdTexture), _sprite(std::move(other._sprite)), _text(std::move(other._text)),
      _isHoldable(other._isHoldable), _callback(std::move(other._callback))
{
}

Button& Button::operator=(Button&& other) noexcept
{
    Component::operator=(std::move(other));
    _idleTexture = other._idleTexture;
    _selectedTexture = other._selectedTexture;
    _holdTexture = other._holdTexture;
    _sprite = std::move(other._sprite);
    _text = std::move(other._text);
    _isHoldable = other._isHoldable;
    _callback = std::move(other._callback);

    return *this;
}

Button::Button(const FontHolder& fonts, const TextureHolder& textures)
    : _idleTexture(&textures.get(TextureId::BUTTON_NORMAL)),
      _selectedTexture(&textures.get(TextureId::BUTTON_SELECTED)),
      _holdTexture(&textures.get(TextureId::BUTTON_PRESSED)), _sprite(*_idleTexture),
      _text("", fonts.get(FontId::SANSATION), 16), _isHoldable(false)
{
    util::centerOrigin(_text);
    const auto bounds = _sprite.getLocalBounds();
    _text.setPosition(bounds.width / 2, bounds.height / 2);
}

void Button::handleEvent(const sf::Event& event)
{
}

void Button::setCallback(Callback callback)
{
    _callback = std::move(callback);
}

void Button::setString(const std::string& str)
{
    _text.setString(str);
    // 위치는 재조정 필요 없음. origin만 재조정하면 위치 알맞게 이동됨.
    util::centerOrigin(_text);
}

void Button::setHoldable(bool isHoldable)
{
    _isHoldable = isHoldable;
}

bool Button::isSelectable() const
{
    return true;
}

void Button::select()
{
    Component::select();

    _sprite.setTexture(*_selectedTexture);
}

void Button::deselect()
{
    Component::deselect();

    _sprite.setTexture(*_idleTexture);
}

void Button::activate()
{
    Component::activate();

    if (_isHoldable)
        _sprite.setTexture(*_holdTexture);

    if (_callback)
        _callback();

    if (!_isHoldable)
        deactivate();
}

void Button::deactivate()
{
    Component::deactivate();

    if (_isHoldable)
        _sprite.setTexture(isSelected() ? *_selectedTexture : *_idleTexture);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_sprite, states);
    target.draw(_text, states);
}

} // namespace gr::gui
