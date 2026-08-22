#ifndef BASE_ERROR_H
#define BASE_ERROR_H

#include "base/base_view.h"

#include <string>
#include <format>

class BaseError : public BaseView {
    std::string m_message;

public:
    BaseError(BaseScreen &screen, std::string message) : BaseView{screen}, m_message{message}
    {
    }

    void build() override {
        lvgl::Label m_label{m_screen.get()};

        m_label
        .center()
        .align(lvgl::Align::Center, 0, 0)
        .set_text(std::format("An error occured:\n{}", m_message))
        .style()
        .text_font(lvgl::Font::montserrat_20());
    }
};

#endif