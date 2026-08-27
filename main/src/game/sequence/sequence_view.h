#ifndef SEQUENCE_VIEW_H
#define SEQUENCE_VIEW_H

#include "game/sequence/sequence_game.h"
#include "ui/view.h"

class SequenceView final : public View {
    SequenceGame &m_game;
    std::vector<const char *> m_buttonMap{};
    std::queue<std::pair<std::uint8_t, bool>> m_displayBuffer{};
    std::chrono::time_point<std::chrono::steady_clock> m_displayTimestamp{};

    lvgl::Label m_timeLabel;
    lvgl::Label m_levelLabel;
    lvgl::ButtonMatrix m_buttonMatrix;

   public:
    SequenceView(lvgl::Object &parent, SequenceGame &game)
        : View{parent}, m_game{game} {}
    void build() override;
    void update() override;
};

#endif