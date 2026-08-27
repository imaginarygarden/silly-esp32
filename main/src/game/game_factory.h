#ifndef GAME_FACTORY_H
#define GAME_FACTORY_H

#include "game/game_descriptor.h"
#include "game/game_route.h"
#include "game/game_runtime.h"

class GameFactory {
    std::vector<GameDescriptor> m_descriptors;

    GameFactory();

   public:
    static GameFactory& instance();
    std::unique_ptr<GameRuntime> create(GameRoute route) const;
    std::optional<GameDescriptor> descriptor(GameRoute route) const;

    std::vector<GameDescriptor> descriptors() const { return m_descriptors; };
};

#endif