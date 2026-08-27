#ifndef GAME_DESCRIPTOR_H
#define GAME_DESCRIPTOR_H

#include <string_view>

#include "game/game_route.h"
#include "game/game_runtime.h"

struct GameDescriptor final {
    GameRoute route{};
    std::string_view name{};
    std::string_view description{};
    std::function<std::unique_ptr<GameRuntime>()> create{};
};

#endif