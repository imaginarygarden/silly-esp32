#ifndef ERROR_H
#define ERROR_H

#include "enum/error_type.h"

#include <string>

struct Error {
    ErrorType type{};
    std::string message{};
};

#endif