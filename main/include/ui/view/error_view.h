#ifndef ERROR_VIEW_H
#define ERROR_VIEW_H

#include "ui/view.h"
#include "app/error.h"

#include <string>
#include <format>

class ErrorView : public View {
    lvgl::Label m_label{m_screen.get()};

public:
    ErrorView(ViewHost &screen) : View{screen}
    {
    }

    void build() override {
        if (!m_screen.getState().error.has_value())
            m_screen.throwError(Error{"Error was not created."});

        m_label
        .center()
        .align(lvgl::Align::Center, 0, 0)
        .set_text(std::format("An error occured:\n{}", m_screen.getState().error->message))
        .style()
        .text_font(lvgl::Font::montserrat_20());
    }
};

#endif