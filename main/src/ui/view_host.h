#ifndef VIEW_HOST_H
#define VIEW_HOST_H

#include <optional>

#include "lvgl_cpp.h"
#include "ui/view.h"

class ViewHost final {
    std::unique_ptr<View> m_view{};
    lvgl::Object m_screen{lvgl::Screen::active()};

   public:
    void reset();
    void set_view(std::function<std::unique_ptr<View>()> create);
    void update_view();
    std::optional<Command> poll_command();

    lvgl::Object &screen() { return m_screen; }
};

#endif