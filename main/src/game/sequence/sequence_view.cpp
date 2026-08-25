#include "game/sequence/sequence_view.h"

#include <freertos/FreeRTOS.h>

void SequenceView::build() {
    m_timeLabel = lvgl::Label{m_parent};
    m_levelLabel = lvgl::Label{m_parent};
    m_buttonMatrix = lvgl::ButtonMatrix{m_parent};

    m_timeLabel
    .align(lvgl::Align::TopLeft, 10, 10);

    m_levelLabel
    .align(lvgl::Align::TopRight, -10, 10);

    m_buttonMatrix
    .align(lvgl::Align::BottomMid)
    .set_size(320, 200)
    .style()
    .radius(0)
    .border_width(0);

    for (std::uint8_t i{}; i < m_game.button_count(); ++i) {
        if (i != 0 && i != m_game.button_count() - 1 && i % m_game.state().cols == 0)
            m_map.push_back("\n");

        m_map.push_back(" ");
    }

    m_map.push_back(nullptr);
    m_buttonMatrix.set_map(m_map.data());

    m_buttonMatrix.on_clicked([this] (lvgl::Event&) {
        if (m_inputBlocked)
            return;

        const std::uint32_t index{m_buttonMatrix.get_selected_button()};

        if (index == LV_BUTTONMATRIX_BUTTON_NONE)
            return;

        m_game.press_button(index);
    });
}

void SequenceView::update() {
    SequenceState state{m_game.state()};

    std::int16_t secondsLeft{static_cast<int16_t>(state.secondsLeft)};

    m_timeLabel.set_text(std::format("{}m {}s", secondsLeft / 60, secondsLeft % 60));
    m_levelLabel.set_text(std::format("Level {}", state.level));

    if (!m_inputBlocked && m_lastSize != state.path.size()) {
        m_lastSize = state.path.size();
        m_inputBlocked = true;
        m_game.pause_time();

        for (uint8_t &num : state.path) {
            m_displayPath.push(num);
        }

        m_buttonMatrix.set_button_ctrl_all(lvgl::ButtonMatrix::Control::Disabled);
    }

    using namespace std::chrono;

    time_point<steady_clock> now = steady_clock::now();
    std::int64_t delay = duration_cast<milliseconds>(now - m_lastDisplayed).count();

    if (m_inputBlocked && delay > 500) {
        if (m_lastButton) {
            m_buttonMatrix.clear_button_ctrl(*m_lastButton, lvgl::ButtonMatrix::Control::Checked);
            m_lastButton.reset();
        } else {
            m_lastButton = m_displayPath.front();
            m_buttonMatrix.set_button_ctrl(*m_lastButton, lvgl::ButtonMatrix::Control::Checked);
            m_displayPath.pop();
        }

        if (m_displayPath.empty() && !m_lastButton) {
            m_buttonMatrix.clear_button_ctrl_all(lvgl::ButtonMatrix::Control::Disabled);
            m_inputBlocked = false;
            m_game.resume_time();
        }

        m_lastDisplayed = now;
    }

}