#include "game/sequence/sequence_game.h"
#include "game/game_result.h"
#include "game/game_status.h"

#include <chrono>

GameStatus SequenceGame::update() {
    using namespace std::chrono;

    time_point<steady_clock> now = steady_clock::now();

    std::int64_t secondsElapsed = duration_cast<seconds>(now - m_state.gameStarted).count();
    std::int64_t minutesElapsed = secondsElapsed / 60;

    if (minutesElapsed >= m_state.minutesLimit)
        return GameStatus::LOSE;

    std::int64_t secondsLeft = m_state.minutesLimit * 60 - secondsElapsed;

    m_state.secondsLeft = secondsLeft;

    return GameStatus::RUNNING;
}

void SequenceGame::start() {
    m_state.gameStarted = std::chrono::steady_clock::now();
}