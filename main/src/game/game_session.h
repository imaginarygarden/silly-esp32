#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <chrono>
#include <optional>

#include "game/game_result.h"
#include "game/game_route.h"
#include "game/game_runtime.h"

class GameSession {
    std::optional<GameRoute> m_route{};
    std::unique_ptr<GameRuntime> m_game{};
    std::chrono::time_point<std::chrono::steady_clock> m_timestamp{};

   public:
    std::function<std::unique_ptr<View>()> start(lvgl::Object& parent);
    std::optional<GameResult> update();
    void reset();
    bool set(GameRoute route);

    bool active() const { return m_game != nullptr; };
    std::optional<GameRoute> route() const { return m_route; };
};

#endif