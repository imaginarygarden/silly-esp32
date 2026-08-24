#ifndef ROUTE_H
#define ROUTE_H

#include <cstdint>

enum class Route : std::uint8_t {
    MENU,
    GAME,
    DEMO,
    SCORE,
    ERROR,
    DESCRIPTION,
    INVITE_RESPONSE,
    INVITE_REQUEST,
};

#endif