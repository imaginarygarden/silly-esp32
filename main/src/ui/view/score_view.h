#ifndef SCORE_VIEW_H
#define SCORE_VIEW_H

#include "game/game_result.h"
#include "ui/view.h"

class ScoreView final : public View {
    GameResult m_result;

    lvgl::Label m_textLabel{m_parent};
    lvgl::Button m_returnButton{m_parent};
    lvgl::Label m_returnLabel{m_returnButton};

   public:
    ScoreView(lvgl::Object& parent, const GameResult result)
        : View{parent}, m_result{result} {}
    void build() override;
};

#endif