#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game/game_session.h"
#include "hardware/display_driver.h"
#include "ui/view_host.h"

class Controller {
    DisplayDriver m_displayDriver{};
    GameSession m_session{};
    ViewHost m_screen{};
    bool m_active{true};

   public:
    void init();
    void update();
    void handle_command(Command command);
    void handle_command(MenuNavigation data);
    void handle_command(ErrorNavigation data);
    void handle_command(DescriptionNavigation data);
    void handle_command(ScoreNavigation data);
    void handle_command(StartCommand data);
    bool active() const { return m_active; }
};

#endif