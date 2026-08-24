#ifndef SEQUENCE_GAME_H
#define SEQUENCE_GAME_H

#include "interface/igame.h"
#include "game/sequence/sequence_state.h"

#include <chrono>
#include <vector>

class SequenceGame : public IGame {
    SequenceState m_state{};

public:
    Status update() override;
    void start() override;
    std::string name() const override { return "Sequence game"; }
    std::string description() const override { return "Remember an increasingly long pattern of button presses."; }
    std::size_t button_count() const { return m_state.cols * m_state.rows; }
    SequenceState state() const { return m_state; }
};

#endif