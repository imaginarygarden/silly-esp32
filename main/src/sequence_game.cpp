#include "game/sequence_game.h"

void SequenceGame::build() {
    m_timeLabel = lvgl::Label{m_screen.get()};
    m_buttonMatrix = lvgl::ButtonMatrix{m_screen.get()};

    m_timeLabel
    .align(lvgl::Align::TopLeft, 10, 10)
    .set_text(std::format("{}m {}s", m_minutesLimit, 0));

    m_buttonMatrix
    .align(lvgl::Align::BottomMid)
    .set_size(320, 200);

    // std::vector<const char *> map{};
    // for (std::size_t i{}; i < getButtonCount(); ++i) {
    //     if (i != 0 && i != getButtonCount() - 1 && i % m_cols == 0)
    //         map.push_back("\n");

    //     map.push_back(std::to_string((int)i).c_str());
    // }

    // m_buttonMatrix.set_map(map.data());
}

void SequenceGame::update() {
    using namespace std::chrono;

    time_point<steady_clock> now = steady_clock::now();

    std::int64_t secondsElapsed = duration_cast<seconds>(now - m_gameStarted).count();
    if (m_lastSecondsElapsed != 0 && m_lastSecondsElapsed == secondsElapsed)
        return;

    m_lastSecondsElapsed = secondsElapsed;
    std::int64_t minutesElapsed = secondsElapsed / 60;

    if (minutesElapsed >= m_minutesLimit)
        m_screen.endGame(Result::LOSE);

    std::int64_t secondsLeft = m_minutesLimit * 60 - secondsElapsed;

    m_timeLabel.set_text(std::format("{}m {}s", secondsLeft / 60, secondsLeft % 60));
}

void SequenceGame::run() {
    m_gameStarted = std::chrono::steady_clock::now();
}