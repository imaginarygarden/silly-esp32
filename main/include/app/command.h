#ifndef COMMAND_H
#define COMMAND_H

#include "app/error.h"
#include "enum/route.h"
#include "enum/game_route.h"
#include "enum/result.h"

#include <string>
#include <variant>

struct MenuNavigation {};

struct ErrorNavigation {
    Error error{};
};

struct DescriptionNavigation {
    GameRoute route{};
};

struct ScoreNavigation {
    Result result{};
};

struct StartCommand {};

using Command = std::variant<
    MenuNavigation,
    ErrorNavigation,
    DescriptionNavigation,
    ScoreNavigation,
    StartCommand
>;

#endif