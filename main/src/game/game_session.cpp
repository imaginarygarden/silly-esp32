#include "game/game_session.h"
#include "game/game_factory.h"

std::function<std::unique_ptr<View>()> GameSession::start(lvgl::Object &parent) {
    if (active() && !running()) {
        m_game->start();
        m_running = true;
        return m_game->create_view(parent);
    }

    return nullptr;
}

bool GameSession::set(GameRoute route) {
    m_game = GameFactory::instance().create(route);

    if (active()) {
        m_route = route;
        m_running = false;
        return true;
    }

    return false;
}

std::optional<GameResult> GameSession::update() { 
    if (!active() || !running())
        return std::nullopt;

    std::optional<GameStatus> status{m_game->update()};

    if (!status || status == GameStatus::RUNNING || status == GameStatus::IDLE)
        return std::nullopt;

    return static_cast<GameResult>(static_cast<std::uint8_t>(*status));
};