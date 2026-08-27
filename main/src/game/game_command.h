#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

#include <variant>

#include "game/game_result.h"

struct PauseGame final {};

struct ResumeGame final {};

struct FinishGame final {
    const GameResult result{};
};

using GameCommand = std::variant<PauseGame, ResumeGame, FinishGame>;

#endif