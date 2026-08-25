#ifndef ERROR_H
#define ERROR_H

#include "app/error_type.h"

#include <string>

struct Error {
    ErrorType type{};
    std::string message{};
};

#endif