#include "ui/view_host.h"

void ViewHost::reset() {
    m_screen.clean();
    m_screen.style()
            .bg_color(lvgl::Color::from_hex(0xFFFFFF));
}

void ViewHost::set_view(std::unique_ptr<View> view) {
    reset();
    m_view = std::move(view);
    m_view->build();
}

std::optional<Command> ViewHost::poll_command() {
    if (!m_view)
        return std::nullopt;

    return m_view->poll_command();
}