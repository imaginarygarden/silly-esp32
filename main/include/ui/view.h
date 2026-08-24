#ifndef VIEW_H
#define VIEW_H

#include "app/command.h"

#include "lvgl_cpp.h"

#include <optional>
#include <queue>

class View {
    std::queue<Command> m_pendingCommands{};

protected:
    lvgl::Object &m_parent;

    void push_command(Command command);

public:
    View(lvgl::Object &parent) : m_parent{parent}
    {
    }

    virtual ~View() = default;

    virtual void build() = 0;
    std::optional<Command> poll_command();
};

#endif