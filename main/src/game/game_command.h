#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

#include <variant>

#include "game/game_result.h"

struct PauseGame {};

struct ResumeGame {};

struct FinishGame {
    GameResult result{};
};

using GameCommand = std::variant<PauseGame, ResumeGame, FinishGame>;

#endif