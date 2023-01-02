#pragma once

#include "enum_as_flags.hpp"

namespace gr
{

enum class NodeCategories
{
    NONE = 0,
    SCENE = 1 << 0,
    PLAYER_AIRCRAFT = 1 << 1,
    FRIEND_AIRCRAFT = 1 << 2,
    ENEMY_AIRCRAFT = 1 << 3,
};

ENUM_AS_FLAGS(NodeCategories);

} // namespace gr
