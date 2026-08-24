#include "game/game_session.h"
#include "game/game_factory.h"

std::unique_ptr<View> GameSession::start(lvgl::Object &parent) {
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

std::optional<Result> GameSession::update() { 
    if (!active() || !running())
        return std::nullopt;

    std::optional<Status> status{m_game->update()};

    if (!status || status == Status::RUNNING || status == Status::IDLE)
        return std::nullopt;

    return static_cast<Result>(static_cast<std::uint8_t>(*status));
};