#ifndef COMMAND_H
#define COMMAND_H

#include <variant>

#include "app/error.h"
#include "game/game_result.h"
#include "game/game_route.h"

struct MenuNavigation {};

struct ErrorNavigation {
    Error error{};
};

struct DescriptionNavigation {
    GameRoute route{};
};

struct ScoreNavigation {
    GameResult result{};
};

struct StartCommand {};

using Command =
    std::variant<MenuNavigation, ErrorNavigation, DescriptionNavigation,
                 ScoreNavigation, StartCommand>;

#endif