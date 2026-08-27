#include "ui/view/description_view.h"

void DescriptionView::build() {
    m_nameLabel = lvgl::Label{m_parent};
    m_descriptionLabel = lvgl::Label{m_parent};
    m_button = lvgl::Button{m_parent};
    m_buttonLabel = lvgl::Label{m_button};

    m_nameLabel.align(lvgl::Align::TopMid, 0, 35)
        .set_size(235, 30)
        .set_text(m_name)
        .style()
        .text_align(lvgl::TextAlign::Center)
        .text_font(lvgl::Font::montserrat_20());

    m_descriptionLabel.align(lvgl::Align::Center)
        .set_size(235, 65)
        .set_text(m_description)
        .style()
        .text_align(lvgl::TextAlign::Center);

    m_button.align(lvgl::Align::BottomMid, 0, -40)
        .set_size(100, 40)
        .on_click([this](lvgl::Event&) { _push_command(StartCommand{}); });

    m_buttonLabel.align(lvgl::Align::Center).set_text("Play");
}