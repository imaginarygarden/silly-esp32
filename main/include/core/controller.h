#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "core/display_driver.h"
#include "base/base_screen.h"
#include "base/base_game.h"

struct State {
    std::unique_ptr<BaseGame> game{};
    Result lastResult{};
    bool playing{false};
    bool active{true};
};

class Controller {
    DisplayDriver m_displayDriver{};
    BaseScreen m_screen{*this};
    State m_state{};

public:
    // runs every 10ms
    void update() { m_screen.update(); }

    State &getState() { return m_state; }
    bool isRunning() const { return m_state.active; }
};

#endif