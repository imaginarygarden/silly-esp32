#ifndef SEQUENCE_GAME_H
#define SEQUENCE_GAME_H

#include "game/game.h"
#include "game/sequence/sequence_command.h"
#include "game/sequence/sequence_phase.h"
#include "game/sequence/sequence_state.h"

class SequenceGame final : public Game {
    SequenceState m_state{};
    SequencePhase m_phase{};
    std::uint8_t m_playerIndex{};

    void _press(const std::uint8_t index);
    void _step_add();
    void _display_finish();

    void _input(const SequencePress command) { _press(command.index); }
    void _input(const SequenceDisplayFinish) { _display_finish(); }

   protected:
    void _start() override;
    void _update(const std::chrono::milliseconds elapsed) override;

   public:
    using Game::input;

    void input(const SequenceCommand command);

    [[nodiscard]]
    SequencePhase sequence_phase() const;

    [[nodiscard]]
    SequenceState state() const;
};

#endif
