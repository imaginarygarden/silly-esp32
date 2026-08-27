#ifndef GAME_DESCRIPTOR_H
#define GAME_DESCRIPTOR_H

#include <string>

#include "game/game_route.h"
#include "game/game_runtime.h"

struct GameDescriptor {
    GameRoute route{};
    std::string name{};
    std::string description{};
    std::function<std::unique_ptr<GameRuntime>()> create{};
};

#endif