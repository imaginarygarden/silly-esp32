#ifndef GAME_RUNTIME_H
#define GAME_RUNTIME_H

#include "ui/view.h"
#include "game/game_status.h"

#include "lvgl_cpp.h"

#include <optional>
#include <memory>

class GameRuntime {
public:
    virtual ~GameRuntime() = default;
    virtual void start() = 0;
    virtual std::optional<GameStatus> update() = 0;
    virtual std::function<std::unique_ptr<View>()> create_view(lvgl::Object &parent) = 0;
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
};

#endif