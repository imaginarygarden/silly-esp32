#ifndef COMMAND_H
#define COMMAND_H

#include <variant>

#include "app/error.h"
#include "game/game_result.h"
#include "game/game_route.h"

struct MenuNavigation final {};

struct ErrorNavigation final {
    const Error error{};
};

struct GameDescriptionNavigation final {
    const GameRoute route{};
};

struct GameScoreNavigation final {
    const GameResult result{};
};

struct GameStartCommand final {};

using Command =
    std::variant<MenuNavigation, ErrorNavigation, GameDescriptionNavigation,
                 GameScoreNavigation, GameStartCommand>;

#endif