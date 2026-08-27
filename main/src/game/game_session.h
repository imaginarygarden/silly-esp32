#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <chrono>
#include <optional>

#include "game/game_descriptor.h"
#include "game/game_result.h"
#include "game/game_route.h"
#include "game/game_runtime.h"

class GameSession final {
    std::optional<GameDescriptor> m_descriptor{};
    std::unique_ptr<GameRuntime> m_game{};
    std::chrono::time_point<std::chrono::steady_clock> m_timestamp{};

   public:
    std::optional<GameResult> update();

    [[nodiscard]]
    std::function<std::unique_ptr<View>()> start(lvgl::Object& parent);

    [[nodiscard]]
    std::optional<GameDescriptor> descriptor() const;

    void reset();
    bool set(GameRoute route);

    bool active() const { return m_game != nullptr; };
};

#endif