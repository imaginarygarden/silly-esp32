#include "game/sequence/sequence_view.h"

#include "game/sequence/sequence_command.h"
#include "game/sequence/sequence_phase.h"
#include "game/sequence/sequence_state.h"

void SequenceView::build() {
    m_timeLabel = lvgl::Label{m_parent};
    m_levelLabel = lvgl::Label{m_parent};
    m_buttonMatrix = lvgl::ButtonMatrix{m_parent};

    m_timeLabel.align(lvgl::Align::TopLeft, 10, 10);
    m_levelLabel.align(lvgl::Align::TopRight, -10, 10);
    m_buttonMatrix.align(lvgl::Align::BottomMid)
        .set_size(320, 200)
        .style()
        .radius(0)
        .border_width(0);

    auto state = m_game.state();
    auto button_count = state.cols * state.rows;

    for (std::uint8_t i{}; i < button_count; ++i) {
        if (i != 0 && i != button_count - 1 && i % state.cols == 0)
            m_buttonMap.push_back("\n");

        m_buttonMap.push_back(" ");
    }

    m_buttonMap.push_back(nullptr);
    m_buttonMatrix.set_map(m_buttonMap.data());

    m_buttonMatrix.on_clicked([this](lvgl::Event &) {
        if (!m_displayBuffer.empty()) return;

        const std::uint32_t index{m_buttonMatrix.get_selected_button()};

        if (index == LV_BUTTONMATRIX_BUTTON_NONE) return;

        m_game.input(SequencePress{static_cast<std::uint8_t>(index)});
    });
}

void SequenceView::update() {
    using namespace std::chrono;

    auto state = m_game.state();

    auto secondsLeft = static_cast<std::int16_t>(state.secondsLeft);

    m_timeLabel.set_text(
        std::format("{}m {}s", secondsLeft / 60, secondsLeft % 60));
    m_levelLabel.set_text(std::format("Level {}", state.level));

    auto now = steady_clock::now();

    if (m_displayBuffer.empty() &&
        m_game.sequence_phase() == SequencePhase::DISPLAY) {
        m_displayTimestamp = now;

        for (auto &num : state.path) {
            m_displayBuffer.push({num, false});
        }

        m_buttonMatrix.set_button_ctrl_all(
            lvgl::ButtonMatrix::Control::Disabled);
    }

    auto delay = duration_cast<milliseconds>(now - m_displayTimestamp);

    if (!m_displayBuffer.empty() && delay > 500ms) {
        auto &[index, highlighted] = m_displayBuffer.front();

        if (highlighted) {
            m_buttonMatrix.clear_button_ctrl(
                index, lvgl::ButtonMatrix::Control::Checked);
            m_displayBuffer.pop();
        } else {
            m_buttonMatrix.set_button_ctrl(
                index, lvgl::ButtonMatrix::Control::Checked);
            highlighted = true;
        }

        if (m_displayBuffer.empty()) {
            m_buttonMatrix.clear_button_ctrl_all(
                lvgl::ButtonMatrix::Control::Disabled);

            m_game.input(SequenceDisplayFinish{});
        }

        m_displayTimestamp = now;
    }
}