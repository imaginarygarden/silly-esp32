#ifndef SEQUENCE_GAME_H
#define SEQUENCE_GAME_H

#include "game/game.h"
#include "game/game_descriptor.h"
#include "game/sequence/sequence_command.h"
#include "game/sequence/sequence_phase.h"
#include "game/sequence/sequence_state.h"

class SequenceGame final : public Game {
    SequenceState m_state{};
    SequencePhase m_phase{};
    std::uint8_t m_playerIndex{};

    void _press(std::uint8_t index);
    void _step_add();
    void _display_finish();

    void _input(SequencePress command) { _press(command.index); }
    void _input(SequenceDisplayFinish) { _display_finish(); }
    std::uint8_t _button_count() const { return m_state.cols * m_state.rows; }

   protected:
    void _start() override;
    void _update(std::chrono::milliseconds elapsed) override;

   public:
    static const GameDescriptor DESCRIPTOR;

    using Game::input;
    void input(SequenceCommand command);

    SequencePhase sequence_phase() const { return m_phase; }
    SequenceState state() const { return m_state; }
};

#endif