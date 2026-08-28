#include "game/sequence/sequence_descriptor.h"

#include "game/sequence/sequence_game.h"
#include "game/sequence/sequence_view.h"
#include "game/typed_game_runtime.h"

const GameDescriptor SEQUENCE_GAME_DESCRIPTOR{
    GameRoute::SEQUENCE, "Sequence Memory",
    "Remember an increasingly long pattern of button presses.", [] {
        return std::make_unique<TypedGameRuntime<SequenceGame, SequenceView>>();
    }};
