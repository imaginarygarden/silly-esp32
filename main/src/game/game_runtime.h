#ifndef GAME_RUNTIME_H
#define GAME_RUNTIME_H

#include "game/game_phase.h"
#include "ui/view.h"

class GameRuntime {
   public:
    virtual ~GameRuntime() = default;

    virtual void start() = 0;
    virtual void update(const std::chrono::milliseconds elapsed) = 0;

    [[nodiscard]]
    virtual GamePhase phase() const = 0;

    [[nodiscard]]
    virtual std::optional<GameResult> result() const = 0;

    [[nodiscard]]
    virtual std::function<std::unique_ptr<View>()> create_view(
        lvgl::Object& parent) = 0;
};

#endif