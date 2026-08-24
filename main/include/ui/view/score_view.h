#ifndef SCORE_VIEW_H
#define SCORE_VIEW_H

#include "ui/view.h"
#include "ui/view_host.h"

class ScoreView : public View {
    lvgl::Label m_textLabel{m_screen.get()};
    lvgl::Button m_returnButton{m_screen.get()};
    lvgl::Label m_returnLabel{m_returnButton};

public:
    ScoreView(ViewHost &screen) : View{screen}
    {
    }

    void build() override;
};

#endif