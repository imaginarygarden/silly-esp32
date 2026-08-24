#ifndef SCORE_VIEW_H
#define SCORE_VIEW_H

#include "ui/view.h"
#include "enum/result.h"

class ScoreView : public View {
    Result m_result;

    lvgl::Label m_textLabel;
    lvgl::Button m_returnButton;
    lvgl::Label m_returnLabel;

public:
    ScoreView(lvgl::Object &parent, Result result) : View{parent}, m_result{result} {}
    void build() override;
};

#endif