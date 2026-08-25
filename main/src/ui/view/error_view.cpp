#include "ui/view/error_view.h"

void ErrorView::build() {
    m_label = lvgl::Label{m_parent};

    m_label
    .center()
    .align(lvgl::Align::Center, 0, 0)
    .set_text(std::format("An error occured:\n{}", m_error.message))
    .style()
    .text_font(lvgl::Font::montserrat_20());
}