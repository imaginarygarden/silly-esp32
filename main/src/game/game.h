#ifndef GAME_H
#define GAME_H

#include <chrono>

#include "game/game_command.h"
#include "game/game_phase.h"
#include "game/game_result.h"

class Game {
    GamePhase m_phase{};
    std::optional<GameResult> m_result{};

    void _input(PauseGame) { _pause(); }
    void _input(ResumeGame) { _resume(); }
    void _input(FinishGame command) { _finish(command.result); }

   protected:
    virtual void _start() = 0;
    virtual void _update(std::chrono::milliseconds elapsed) = 0;

    void _pause();
    void _resume();
    void _finish(GameResult result);

   public:
    virtual ~Game() = default;

    void update(std::chrono::milliseconds elapsed);
    void start();
    void input(GameCommand command);

    GamePhase phase() const { return m_phase; }
    std::optional<GameResult> result() const { return m_result; }
};

#endif