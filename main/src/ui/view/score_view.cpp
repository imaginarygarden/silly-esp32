#include "ui/view/score_view.h"

#include <format>
#include <unordered_map>

namespace {

std::unordered_map<GameResult, std::string> RESULT_MESSAGES{
    {GameResult::WIN, "You won!"},
    {GameResult::LOSE, "You lost :("},
    {GameResult::TIE, "A tie -_-"},
};

}

void ScoreView::build() {
    m_textLabel.center()
        .align(lvgl::Align::Center, 0, 0)
        .set_text(std::format("{}", RESULT_MESSAGES[m_result]))
        .style()
        .text_font(lvgl::Font::montserrat_20());

    m_button.get()
        .align(lvgl::Align::Center, 0, 40)
        .on_click([this](lvgl::Event&) { _push_command(MenuNavigation{}); });

    m_button.get_label().set_text("Return to menu");
}