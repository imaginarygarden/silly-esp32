#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "hardware/display_driver.h"
#include "ui/view_host.h"
#include "interface/igame.h"
#include "game/game_session.h"
#include "app/state.h"
#include "app/error.h"

class Controller {
    DisplayDriver m_displayDriver{};
    State m_state{};
    GameSession m_session{};
    ViewHost m_screen{};

public:
    Controller();

    void update();
    State &state() { return m_state; }
    bool active() const { return m_state.active; }

    void handle_command(Command command);
    void handle_command(MenuNavigation data);
    void handle_command(ErrorNavigation data);
    void handle_command(DescriptionNavigation data);
    void handle_command(ScoreNavigation data);
    void handle_command(StartCommand data);
};

#endif