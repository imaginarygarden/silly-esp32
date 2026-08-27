#ifndef GAME_H
#define GAME_H

#include <chrono>

#include "game/game_command.h"
#include "game/game_phase.h"
#include "game/game_result.h"

class Game {
    GamePhase m_phase{};
    std::optional<GameResult> m_result{};

    void _input(const PauseGame) { _pause(); }
    void _input(const ResumeGame) { _resume(); }
    void _input(const FinishGame command) { _finish(command.result); }

   protected:
    virtual void _start() = 0;
    virtual void _update(const std::chrono::milliseconds elapsed) = 0;

    void _pause();
    void _resume();
    void _finish(const GameResult result);

   public:
    virtual ~Game() = default;

    void update(const std::chrono::milliseconds elapsed);
    void start();
    void input(const GameCommand command);

    [[nodiscard]]
    GamePhase phase() const;

    [[nodiscard]]
    std::optional<GameResult> result() const;
};

#endif