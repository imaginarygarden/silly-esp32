#include "game/game_factory.h"

#include "game/sequence/sequence_descriptor.h"

GameFactory::GameFactory() : m_descriptors{SEQUENCE_GAME_DESCRIPTOR} {}

GameFactory& GameFactory::instance() {
    static GameFactory object{};
    return object;
}

std::optional<GameDescriptor> GameFactory::descriptor(
    const GameRoute route) const {
    for (auto& descriptor : m_descriptors) {
        if (descriptor.route == route) return descriptor;
    }

    return std::nullopt;
}

const std::vector<GameDescriptor>& GameFactory::descriptors() const {
    return m_descriptors;
};
