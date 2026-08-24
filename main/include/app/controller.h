#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "hardware/display_driver.h"
#include "ui/view_host.h"
#include "game/game.h"
#include "app/state.h"

class Controller {
    DisplayDriver m_displayDriver{};
    State m_state{};
    ViewHost m_screen{*this};

public:
    // runs every 10ms
    void update() { m_screen.update(); }

    State &getState() { return m_state; }
    bool isRunning() const { return m_state.active; }
};

#endif