#include "game/sequence/sequence_game.h"

#include <algorithm>
#include <chrono>

#include "game/game_command.h"
#include "game/game_result.h"
#include "game/sequence/sequence_phase.h"
#include "game/sequence/sequence_view.h"
#include "game/typed_game_runtime.h"

void SequenceGame::_press(const std::uint8_t index) {
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

    auto button_count = m_state.cols * m_state.rows;

    auto num = static_cast<std::uint8_t>(rand() % button_count);

    while (!m_state.path.empty() && num == m_state.path.back()) {
        num = static_cast<std::uint8_t>(rand() % button_count);
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

void SequenceGame::_update(const std::chrono::milliseconds elapsed) {
    m_state.secondsLeft =
        std::clamp<double>(m_state.secondsLeft - elapsed.count() / 1000.0, 0,
                           std::numeric_limits<double>::max());

    if (m_state.secondsLeft <= 0) {
        _finish(GameResult::LOSE);
    }
}

const GameDescriptor SequenceGame::DESCRIPTOR{
    GameRoute::SEQUENCE, "Sequence Memory",
    "Remember an increasingly long pattern of button presses.", [] {
        return std::make_unique<TypedGameRuntime<SequenceGame, SequenceView>>();
    }};

void SequenceGame::input(const SequenceCommand command) {
    if (phase() == GamePhase::IDLE || phase() == GamePhase::FINISHED) return;

    std::visit([this](auto&& value) { _input(std::move(value)); },
               std::move(command));
}

SequencePhase SequenceGame::sequence_phase() const { return m_phase; }

SequenceState SequenceGame::state() const { return m_state; }