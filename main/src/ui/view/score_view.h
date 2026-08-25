#ifndef SCORE_VIEW_H
#define SCORE_VIEW_H

#include "game/game_result.h"
#include "ui/view.h"

class ScoreView : public View {
    GameResult m_result;

    lvgl::Label m_textLabel;
    lvgl::Button m_returnButton;
    lvgl::Label m_returnLabel;

   public:
    ScoreView(lvgl::Object& parent, GameResult result)
        : View{parent}, m_result{result} {}
    void build() override;
};

#endif