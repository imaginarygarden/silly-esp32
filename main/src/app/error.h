#ifndef ERROR_H
#define ERROR_H

#include <string_view>

#include "app/error_type.h"

struct Error final {
    ErrorType type{};
    std::string_view message{};
};

#endif