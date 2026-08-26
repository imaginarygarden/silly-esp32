#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <optional>

#include "game/game_result.h"
#include "game/game_route.h"
#include "game/game_runtime.h"
#include "lvgl_cpp.h"
#include "ui/view.h"

class GameSession {
    std::optional<GameRoute> m_route{};
    std::unique_ptr<GameRuntime> m_game{};
    bool m_running{};

   public:
    std::function<std::unique_ptr<View>()> start(lvgl::Object& parent);
    std::optional<GameResult> update();
    std::optional<GameRoute> route() const { return m_route; };
    std::optional<std::string> name() const {
        return active() ? std::optional{m_game->name()} : std::nullopt;
    }
    std::optional<std::string> description() const {
        return active() ? std::optional{m_game->description()} : std::nullopt;
    }
    void reset() {
        m_route = std::nullopt;
        m_game = nullptr;
        m_running = false;
    }
    bool set(GameRoute route);
    bool active() const { return m_game != nullptr; };
    bool running() const { return m_running; }
};

#endif