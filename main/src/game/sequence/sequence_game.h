#ifndef SEQUENCE_GAME_H
#define SEQUENCE_GAME_H

#include "game/game.h"
#include "game/sequence/sequence_state.h"

class SequenceGame : public Game {
    SequenceState m_state{};

   public:
    GameStatus update() override;
    void start() override;
    std::string name() const override { return "Sequence game"; }
    std::string description() const override {
        return "Remember an increasingly long pattern of button presses.";
    }
    std::uint8_t button_count() const { return m_state.cols * m_state.rows; }
    SequenceState state() const { return m_state; }
    void press_button(std::uint8_t index);
    void pause_time();
    void resume_time();
};

#endif