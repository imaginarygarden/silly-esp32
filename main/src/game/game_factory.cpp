#include "game/game_factory.h"

#include "game/sequence/sequence_game.h"
#include "game/sequence/sequence_view.h"
#include "game/typed_game_runtime.h"

std::unique_ptr<GameRuntime> GameFactory::create(GameRoute route) {
    switch (route) {
        case GameRoute::SEQUENCE:
            return std::make_unique<
                TypedGameRuntime<SequenceGame, SequenceView>>();
        default:
            return nullptr;
    }
}