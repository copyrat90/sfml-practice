#pragma once

#include <type_traits>

namespace sf
{
class Texture;
class Shader;
} // namespace sf

namespace gr
{

template <typename Resource, typename Id, int IdMaxCount>
    requires std::is_enum_v<Id>
class ResourceHolder;

enum class TextureId
{
    PLAYER,
    TILEMAP,
    UI,

    MAX_COUNT
};

enum class ShaderId
{
    HEAT_HAZE,

    MAX_COUNT
};

using TextureHolder = ResourceHolder<sf::Texture, TextureId, (int)TextureId::MAX_COUNT>;

using ShaderHolder = ResourceHolder<sf::Shader, ShaderId, (int)ShaderId::MAX_COUNT>;

} // namespace gr
