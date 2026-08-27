#include "game/game_session.h"

#include <chrono>

#include "game/game_factory.h"
#include "game/game_phase.h"

std::function<std::unique_ptr<View>()> GameSession::start(
    lvgl::Object& parent) {
    if (m_game && m_game->phase() == GamePhase::IDLE) {
        m_timestamp = std::chrono::steady_clock::now();

        m_game->start();

        return m_game->create_view(parent);
    }

    return nullptr;
}

std::optional<GameResult> GameSession::update() {
    using namespace std::chrono;

    if (!m_game) return std::nullopt;

    milliseconds elapsed =
        duration_cast<milliseconds>(steady_clock::now() - m_timestamp);

    m_game->update(elapsed);

    m_timestamp = steady_clock::now();

    return m_game->result();
};

void GameSession::reset() {
    m_descriptor.reset();
    m_game.reset();
}

bool GameSession::set(GameRoute route) {
    auto descriptor = GameFactory::instance().descriptor(route);

    if (!descriptor) {
        return false;
    }

    m_game = descriptor->create();

    if (m_game) {
        m_descriptor = descriptor;
        return true;
    }

    return false;
}
