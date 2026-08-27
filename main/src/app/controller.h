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

    void _input(MenuNavigation data);
    void _input(ErrorNavigation data);
    void _input(DescriptionNavigation data);
    void _input(ScoreNavigation data);
    void _input(StartCommand data);

   public:
    void init();
    void update();
    void input(Command command);

    bool active() const { return m_active; }
};

#endif