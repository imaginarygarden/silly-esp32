#ifndef RESULT_H
#define RESULT_H

#include <cstdint>

enum class Result : std::uint8_t {
    WIN,
    LOSE,
    TIE,
    ERROR
};

#endif