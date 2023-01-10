#pragma once

#include <type_traits>

namespace sf
{
class Texture;
class Font;
} // namespace sf

namespace gr
{

template <typename Resource, typename Id, int IdMaxCount>
    requires std::is_enum_v<Id>
class ResourceHolder;

enum class TextureId
{
    DESERT,
    EAGLE,
    RAPTOR,

    TITLE_SCREEN,

    TOTAL_COUNT
};

enum class FontId
{
    SANSATION,

    TOTAL_COUNT
};

using TextureHolder = ResourceHolder<sf::Texture, TextureId, (int)TextureId::TOTAL_COUNT>;
using FontHolder = ResourceHolder<sf::Font, FontId, (int)FontId::TOTAL_COUNT>;

} // namespace gr
