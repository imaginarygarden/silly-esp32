#ifndef GAME_DESCRIPTOR_H
#define GAME_DESCRIPTOR_H

#include <string>

#include "game/game_route.h"

struct GameDescriptor {
    GameRoute route{};
    std::string name{};
    std::string description{};
};

#endif