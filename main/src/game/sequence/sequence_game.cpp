#include "game/sequence/sequence_game.h"
#include "game/game_result.h"
#include "game/game_status.h"

#include <chrono>

GameStatus SequenceGame::update() {
    using namespace std::chrono;

    if (!m_state.paused) {
        time_point<steady_clock> now = steady_clock::now();
        std::int64_t millisecondsElapsed = duration_cast<milliseconds>(now - m_state.lastMeasured).count();

        m_state.lastMeasured = now;
        m_state.secondsLeft -= millisecondsElapsed / 1000.0;
    }

    if (m_state.secondsLeft <= 0 || m_state.lost)
        return GameStatus::LOSE;

    return GameStatus::RUNNING;
}

void SequenceGame::start() {
    if (m_state.started)
        return;

    m_state.lastMeasured = std::chrono::steady_clock::now();
    m_state.started = true;
    m_state.path.push_back(rand() % button_count());
}

void SequenceGame::press_button(std::uint8_t index) {
    if (!m_state.started || m_state.lost || m_state.paused)
        return;

    if (m_state.path[m_state.playerIndex] != index)
        m_state.lost = true;

    m_state.playerIndex++;

    if (m_state.playerIndex >= m_state.path.size()) {
        std::uint8_t num{static_cast<std::uint8_t>(rand() % button_count())};
        while (!m_state.path.empty() && num == m_state.path.back()) { num = rand() % button_count(); }

        m_state.path.push_back(num);
        m_state.playerIndex = 0;
        m_state.level++;
    }
}

void SequenceGame::pause_time() {
    m_state.paused = true;
}

void SequenceGame::resume_time() {
    m_state.paused = false;
    m_state.lastMeasured = std::chrono::steady_clock::now();
}