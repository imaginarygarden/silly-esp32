#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H

#include <cstdint>

enum class ErrorType : std::uint8_t {
    UNDEFINED,
    UNEXPECTED,
    NETWORK,
};

#endif