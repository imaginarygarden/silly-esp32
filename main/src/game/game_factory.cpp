#include "game/game_factory.h"
#include "game/game_runtime.h"
#include "game/sequence/sequence_game.h"
#include "game/sequence/sequence_view.h"

std::unique_ptr<IGameRuntime> GameFactory::create(GameRoute route) {
    switch (route) {
        case GameRoute::SEQUENCE:
            return std::make_unique<GameRuntime<SequenceGame, SequenceView>>();
        default:
            return nullptr;
    }
}