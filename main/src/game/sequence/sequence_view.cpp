#include "game/sequence/sequence_view.h"

void SequenceView::build() {
    m_timeLabel = lvgl::Label{m_parent};
    m_buttonMatrix = lvgl::ButtonMatrix{m_parent};

    m_timeLabel
    .align(lvgl::Align::TopLeft, 10, 10)
    .set_text(std::format("{}m {}s", m_game.state().secondsLeft / 60, m_game.state().secondsLeft % 60));

    m_buttonMatrix
    .align(lvgl::Align::BottomMid)
    .set_size(320, 200);

    // std::vector<const char *> map{};
    // for (std::size_t i{}; i < button_count(); ++i) {
    //     if (i != 0 && i != button_count() - 1 && i % m_cols == 0)
    //         map.push_back("\n");

    //     map.push_back(std::to_string((int)i).c_str());
    // }

    // m_buttonMatrix.set_map(map.data());
}