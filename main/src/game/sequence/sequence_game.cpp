#include "game/sequence/sequence_game.h"

#include <algorithm>
#include <chrono>

#include "game/game_command.h"
#include "game/game_result.h"
#include "game/sequence/sequence_phase.h"

void SequenceGame::_press(std::uint8_t index) {
    if (m_phase != SequencePhase::ACTIVE) return;

    if (m_state.path[m_playerIndex] != index) {
        _finish(GameResult::LOSE);
        return;
    }

    m_playerIndex++;

    if (m_playerIndex >= m_state.path.size()) {
        _step_add();
        m_state.level++;
    }
}

void SequenceGame::_step_add() {
    if (m_phase != SequencePhase::ACTIVE) return;

    auto num = static_cast<std::uint8_t>(rand() % _button_count());

    while (!m_state.path.empty() && num == m_state.path.back()) {
        num = static_cast<std::uint8_t>(rand() % _button_count());
    }

    m_state.path.push_back(num);
    m_playerIndex = 0;
    m_phase = SequencePhase::DISPLAY;
    input(PauseGame{});
}

void SequenceGame::_display_finish() {
    if (m_phase == SequencePhase::DISPLAY) {
        m_phase = SequencePhase::ACTIVE;
        input(ResumeGame{});
    }
}

void SequenceGame::_start() { _step_add(); }

void SequenceGame::_update(std::chrono::milliseconds elapsed) {
    m_state.secondsLeft -= elapsed.count() / 1000.0;
}

void SequenceGame::input(SequenceCommand command) {
    std::visit([this](auto&& value) { _input(std::move(value)); },
               std::move(command));
}