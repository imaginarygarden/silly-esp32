#ifndef SEQUENCE_VIEW_H
#define SEQUENCE_VIEW_H

#include "ui/view.h"
#include "game/sequence/sequence_game.h"

class SequenceView final : public View {
    SequenceGame &m_game;

    lvgl::Label m_timeLabel;
    lvgl::ButtonMatrix m_buttonMatrix;

public:
    SequenceView(lvgl::Object &parent, SequenceGame &game) : View{parent}, m_game{game} {}
    void build() override;
};

#endif