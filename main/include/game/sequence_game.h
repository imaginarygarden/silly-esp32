#ifndef SEQUENCE_GAME_H
#define SEQUENCE_GAME_H

#include "base/base_game.h"
#include "base/base_screen.h"

#include <chrono>
#include <vector>

class SequenceGame : public BaseGame {
    lvgl::Label m_timeLabel;
    lvgl::ButtonMatrix m_buttonMatrix;
    uint8_t m_cols{3};
    uint8_t m_rows{3};
    std::int64_t m_lastSecondsElapsed{};
    std::size_t m_minutesLimit{1};
    std::size_t m_level{1};
    std::size_t m_historyIndex{};
    std::vector<uint8_t> m_history{};
    std::chrono::time_point<std::chrono::steady_clock> m_gameStarted{};

public:
    SequenceGame(BaseScreen &screen) : BaseGame{screen}
    {
    }

    virtual void build() override;
    
    virtual void update() override;

    virtual void run() override;

    virtual std::string getName() const { return "Sequence game"; }

    virtual std::string getDescription() const override { return "Remember an increasingly long pattern of button presses."; }

    std::size_t getButtonCount() const { return m_cols * m_rows; }
};

#endif