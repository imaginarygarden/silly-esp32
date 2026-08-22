#ifndef SCORE_VIEW_H
#define SCORE_VIEW_H

#include "base/base_view.h"
#include "base/base_screen.h"

class ScoreView : public BaseView {
    Result m_result;
    lvgl::Label m_textLabel{m_screen.get()};
    lvgl::Button m_returnButton{m_screen.get()};
    lvgl::Label m_returnLabel{m_returnButton};

public:
    ScoreView(BaseScreen &screen, Result result) : BaseView{screen}, m_result{result}
    {
    }

    void build() override;
};

#endif