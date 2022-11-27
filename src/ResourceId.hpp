#pragma once

#include <type_traits>

namespace sf
{
class Texture;
}

namespace gr
{

template <typename Resource, typename Id, int IdMaxCount>
    requires std::is_enum_v<Id>
class ResourceHolder;

enum class TextureId
{
    SPLASH_RAT,

    MAX_COUNT
};

using TextureHolder = ResourceHolder<sf::Texture, TextureId, (int)TextureId::MAX_COUNT>;

} // namespace gr
