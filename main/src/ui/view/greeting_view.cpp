#include "ui/view/greeting_view.h"

#include "app/command.h"

void GreetingView::build() {
    m_label.set_size(235, 65)
        .set_text(
            "The project is currently in alpha and bugs may occur. Please "
            "report "
            "any problems using issues function on GitHub.")
        .align(lvgl::Align::Center, 0, -20)
        .style()
        .text_align(lvgl::TextAlign::Center);

    m_button.get()
        .align(lvgl::Align::Center, 0, 50)
        .on_click([this](lvgl::Event &) { _push_command(MenuNavigation{}); });

    m_button.get_label().set_text("Continue");
}
