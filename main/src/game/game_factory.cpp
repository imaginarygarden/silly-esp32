#include "game/game_factory.h"

#include "game/sequence/sequence_game.h"
#include "game/sequence/sequence_view.h"
#include "game/typed_game_runtime.h"

GameFactory::GameFactory() : m_descriptors{SequenceGame::DESCRIPTOR} {}

GameFactory& GameFactory::instance() {
    static GameFactory object{};
    return object;
}

std::unique_ptr<GameRuntime> GameFactory::create(GameRoute route) const {
    switch (route) {
        case GameRoute::SEQUENCE:
            return std::make_unique<
                TypedGameRuntime<SequenceGame, SequenceView>>();
        default:
            return nullptr;
    }
}

std::optional<GameDescriptor> GameFactory::descriptor(GameRoute route) const {
    for (auto& descriptor : m_descriptors) {
        if (descriptor.route == route) return descriptor;
    }

    return std::nullopt;
}