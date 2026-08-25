#ifndef GAME_FACTORY_H
#define GAME_FACTORY_H

#include "interface/igame.h"
#include "enum/game_route.h"
#include "interface/igame_runtime.h"

#include <memory>

class GameFactory {
    GameFactory() {}

public:
    static GameFactory &instance() { static GameFactory object{}; return object; }
    std::unique_ptr<IGameRuntime> create(GameRoute route);
};

#endif