#ifndef GAME_FACTORY_H
#define GAME_FACTORY_H

#include "game/game_descriptor.h"
#include "game/game_route.h"

class GameFactory final {
    const std::vector<GameDescriptor> m_descriptors;

    GameFactory();

   public:
    static GameFactory& instance();

    [[nodiscard]]
    std::optional<GameDescriptor> descriptor(const GameRoute route) const;

    [[nodiscard]]
    const std::vector<GameDescriptor>& descriptors() const;
};

#endif