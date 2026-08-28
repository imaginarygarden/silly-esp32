#ifndef SCORE_VIEW_H
#define SCORE_VIEW_H

#include "game/game_result.h"
#include "ui/component/button.h"
#include "ui/view.h"

class ScoreView final : public View {
    GameResult m_result;

    lvgl::Label m_textLabel{m_parent};
    Button m_button{m_parent};

   public:
    ScoreView(lvgl::Object& parent, const GameResult result)
        : View{parent}, m_result{result} {}
    void build() override;
};

#endif