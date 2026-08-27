#include "ui/view.h"

void View::_push_command(Command command) {
    m_pendingCommands.push(std::move(command));
}

std::optional<Command> View::poll_command() {
    if (m_pendingCommands.empty()) return std::nullopt;

    const auto command = m_pendingCommands.front();

    m_pendingCommands.pop();

    return command;
}