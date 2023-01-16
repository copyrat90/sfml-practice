#pragma once

#include "Component.hpp"

#include <SFML/Graphics/Text.hpp>

#include "../ResourceId.hpp"

namespace gr::gui
{

class Label : public Component
{
public:
    using UPtr = std::unique_ptr<Label>;

public:
    Label(Label&&) noexcept;
    Label& operator=(Label&&) noexcept;

public:
    Label(const std::string&, const FontHolder&);

    void handleEvent(const sf::Event&) override;

    bool isSelectable() const override;

    void setString(const std::string&);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Text _text;
};

} // namespace gr::gui
