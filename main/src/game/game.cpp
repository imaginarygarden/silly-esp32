#include "game/game.h"

#include "game/game_phase.h"

void Game::_pause() {
    if (m_phase == GamePhase::RUNNING) m_phase = GamePhase::PAUSED;
}

void Game::_resume() {
    if (m_phase == GamePhase::PAUSED) m_phase = GamePhase::RUNNING;
}

void Game::_finish(GameResult result) {
    if (m_phase == GamePhase::RUNNING || m_phase == GamePhase::PAUSED) {
        m_phase = GamePhase::FINISHED;
        m_result = result;
    }
}

void Game::update(std::chrono::milliseconds elapsed) {
    if (m_phase == GamePhase::RUNNING) _update(elapsed);
}

void Game::start() {
    if (m_phase == GamePhase::IDLE) {
        m_phase = GamePhase::RUNNING;
        _start();
    }
}

void Game::input(GameCommand command) {
    std::visit([this](auto&& value) { _input(std::move(value)); },
               std::move(command));
}