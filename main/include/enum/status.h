#ifndef STATUS_H
#define STATUS_H

#include <cstdint>

enum class Status : std::uint8_t {
    WIN,
    LOSE,
    TIE,
    ERROR,
    RUNNING,
    IDLE,
};

#endif