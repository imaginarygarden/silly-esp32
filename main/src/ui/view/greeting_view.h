#ifndef GREETING_VIEW_H
#define GREETING_VIEW_H

#include "ui/component/button.h"
#include "ui/view.h"

class GreetingView final : public View {
    lvgl::Label m_label{m_parent};
    Button m_button{m_parent};

   public:
    GreetingView(lvgl::Object &parent) : View{parent} {}

    void build() override;
};

#endif