#ifndef GAME_FACTORY_H
#define GAME_FACTORY_H

#include <memory>

#include "game/game_route.h"
#include "game/game_runtime.h"

class GameFactory {
    GameFactory() {}

   public:
    static GameFactory& instance() {
        static GameFactory object{};
        return object;
    }
    std::unique_ptr<GameRuntime> create(GameRoute route);
};

#endif