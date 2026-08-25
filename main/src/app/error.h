#ifndef ERROR_H
#define ERROR_H

#include <string>

#include "app/error_type.h"

struct Error {
    ErrorType type{};
    std::string message{};
};

#endif