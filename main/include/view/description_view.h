#ifndef DESCRIPTION_VIEW_H
#define DESCRIPTION_VIEW_H

#include "base/base_view.h"
#include "base/base_screen.h"

class DescriptionView : public BaseView {
    lvgl::Label m_nameLabel{m_screen.get()};
    lvgl::Label m_descriptionLabel{m_screen.get()};
    lvgl::Button m_button{m_screen.get()};
    lvgl::Label m_buttonLabel{m_button};

public:
    DescriptionView(BaseScreen &screen) : BaseView{screen}
    {
    }

    void build() override {
        m_nameLabel
        .align(lvgl::Align::TopMid, 0, 35)
        .set_size(235, 30)
        .set_text(m_screen.getState().game->getName())
        .style()
        .text_align(lvgl::TextAlign::Center)
        .text_font(lvgl::Font::montserrat_20());

        m_descriptionLabel
        .align(lvgl::Align::Center)
        .set_size(235, 65)
        .set_text(m_screen.getState().game->getDescription())
        .style()
        .text_align(lvgl::TextAlign::Center);

        m_button
        .align(lvgl::Align::BottomMid, 0, -40)
        .set_size(100, 40)
        .on_click([this] (lvgl::Event&) {
            m_screen.runGame();
        });

        m_buttonLabel
        .align(lvgl::Align::Center)
        .set_text("Play");
    };
};

#endif