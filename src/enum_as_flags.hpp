#ifndef COPYRAT90_ENUM_AS_FLAGS_HPP
#define COPYRAT90_ENUM_AS_FLAGS_HPP

#include <type_traits>

#define ENUM_AS_FLAGS(Enum) \
    static_assert(std::is_enum<Enum>::value, "Passed type is not an enum."); \
\
    inline constexpr bool operator!(Enum a) \
    { \
        using Int = typename std::underlying_type<Enum>::type; \
        return !static_cast<Int>(a); \
    } \
\
    inline constexpr Enum operator~(Enum a) \
    { \
        using Int = typename std::underlying_type<Enum>::type; \
        return static_cast<Enum>(~static_cast<Int>(a)); \
    } \
\
    inline constexpr Enum operator|(Enum a, Enum b) \
    { \
        using Int = typename std::underlying_type<Enum>::type; \
        return static_cast<Enum>(static_cast<Int>(a) | static_cast<Int>(b)); \
    } \
\
    inline constexpr Enum& operator|=(Enum& a, Enum b) \
    { \
        return a = a | b; \
    } \
\
    inline constexpr Enum operator&(Enum a, Enum b) \
    { \
        using Int = typename std::underlying_type<Enum>::type; \
        return static_cast<Enum>(static_cast<Int>(a) & static_cast<Int>(b)); \
    } \
\
    inline constexpr Enum& operator&=(Enum& a, Enum b) \
    { \
        return a = a & b; \
    } \
\
    inline constexpr Enum operator^(Enum a, Enum b) \
    { \
        using Int = typename std::underlying_type<Enum>::type; \
        return static_cast<Enum>(static_cast<Int>(a) ^ static_cast<Int>(b)); \
    } \
\
    inline constexpr Enum& operator^=(Enum& a, Enum b) \
    { \
        return a = a ^ b; \
    }

#endif
