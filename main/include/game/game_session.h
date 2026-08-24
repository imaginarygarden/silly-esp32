#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "interface/igame.h"
#include "interface/igame_runtime.h"
#include "ui/view.h"
#include "enum/game_route.h"
#include "enum/result.h"

#include "lvgl_cpp.h"

#include <optional>

class GameSession {
    std::optional<GameRoute> m_route{};
    std::unique_ptr<IGameRuntime> m_game{};
    bool m_running{};

public:
    std::unique_ptr<View> start(lvgl::Object &parent);
    bool set(GameRoute route);
    std::optional<Result> update();

    void reset() { m_route = std::nullopt; m_game = nullptr; m_running = false; }
    std::optional<GameRoute> route() const { return m_route; };
    bool active() const { return m_game != nullptr; };
    bool running() const { return m_running; }
    std::optional<std::string> name() const { return active() ? std::optional{m_game->name()} : std::nullopt; }
    std::optional<std::string> description() const { return active() ? std::optional{m_game->description()} : std::nullopt; }
};

#endif