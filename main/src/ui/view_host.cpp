#include "ui/view_host.h"

#include <functional>

void ViewHost::reset() {
    m_screen.clean();
    m_screen.style()
            .bg_color(lvgl::Color::from_hex(0xFFFFFF));
}

void ViewHost::set_view(std::function<std::unique_ptr<View>()> create) {
    m_view.reset();
    reset();
    m_view = create();
    m_view->build();
}

std::optional<Command> ViewHost::poll_command() {
    if (!m_view)
        return std::nullopt;

    return m_view->poll_command();
}