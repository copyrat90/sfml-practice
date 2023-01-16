#pragma once

#include "Component.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <functional>

#include "../ResourceId.hpp"

namespace gr::gui
{

class Button : public Component
{
public:
    using UPtr = std::unique_ptr<Button>;
    using Callback = std::function<void()>;

public:
    Button(Button&&) noexcept;
    Button& operator=(Button&&) noexcept;

public:
    Button(const FontHolder&, const TextureHolder&);

    void handleEvent(const sf::Event&) override;

    void setCallback(Callback);
    void setString(const std::string&);
    void setHoldable(bool isHoldable);

    bool isSelectable() const override;

    void select() override;
    void deselect() override;

    void activate() override;
    void deactivate() override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    const sf::Texture* _idleTexture;
    const sf::Texture* _selectedTexture;
    const sf::Texture* _holdTexture;

    sf::Sprite _sprite;
    sf::Text _text;

    bool _isHoldable;
    Callback _callback;
};

} // namespace gr::gui
