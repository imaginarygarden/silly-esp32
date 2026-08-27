#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game/game_session.h"
#include "hardware/display_driver.h"
#include "ui/view_host.h"

class Controller final {
    const DisplayDriver m_driver{};
    GameSession m_session{};
    ViewHost m_host{};
    bool m_active{true};

    void _input(const MenuNavigation data);
    void _input(const ErrorNavigation data);
    void _input(const GameDescriptionNavigation data);
    void _input(const GameScoreNavigation data);
    void _input(const GameStartCommand data);

   public:
    void init();
    void update();
    void input(const Command command);

    [[nodiscard]]
    bool active() const;
};

#endif