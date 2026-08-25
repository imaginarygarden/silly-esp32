#ifndef SEQUENCE_VIEW_H
#define SEQUENCE_VIEW_H

#include "ui/view.h"
#include "game/sequence/sequence_game.h"

class SequenceView final : public View {
    SequenceGame &m_game;
    std::vector<const char*> m_map{};
    std::uint8_t m_lastSize{};
    std::queue<uint8_t> m_displayPath{};
    bool m_inputBlocked{};
    std::chrono::time_point<std::chrono::steady_clock> m_lastDisplayed{};
    std::optional<uint8_t> m_lastButton{};

    lvgl::Label m_timeLabel;
    lvgl::Label m_levelLabel;
    lvgl::ButtonMatrix m_buttonMatrix;

public:
    SequenceView(lvgl::Object &parent, SequenceGame &game) : View{parent}, m_game{game} {}
    void build() override;
    void update() override;
};

#endif