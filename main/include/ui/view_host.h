#ifndef VIEW_HOST_H
#define VIEW_HOST_H

#include "ui/view.h"

#include "lvgl_cpp.h"

#include <optional>

class ViewHost {
    std::optional<Route> m_route{};
    std::unique_ptr<View> m_view{};
    lvgl::Object m_screen{lvgl::Screen::active()};

public:
    void reset();
    void set_view(std::unique_ptr<View> view);
    std::optional<Command> poll_command();
    operator lvgl::Object&() { return m_screen; }
};

#endif