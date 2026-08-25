#ifndef GAME_STATUS_H
#define GAME_STATUS_H

#include <cstdint>

enum class GameStatus : std::uint8_t {
    WIN,
    LOSE,
    TIE,
    ERROR,
    RUNNING,
    IDLE,
};

#endif