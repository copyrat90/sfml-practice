#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <cmath>
#include <string>

namespace gr::util
{

template <typename TObj>
void centerOrigin(TObj& obj)
{
    // bounds.left와 bounds.top은 0이 아닐 수 있음.
    // sf::Text의 경우, 바닥 기준 정렬이라 offset 존재하기 때문.
    // https://en.sfml-dev.org/forums/index.php?topic=27711.0

    const sf::FloatRect bounds = obj.getLocalBounds();
    obj.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

std::string toString(sf::Keyboard::Key key);

} // namespace gr::util
