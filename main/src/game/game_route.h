#ifndef GAME_ROUTE_H
#define GAME_ROUTE_H

#include <cstdint>

enum class GameRoute : std::uint8_t {
    SEQUENCE,
    REACTION,
    AIM,
};

#endif