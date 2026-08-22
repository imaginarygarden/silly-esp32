#include "view/score_view.h"

#include <unordered_map>

namespace {

std::unordered_map<Result, std::string> RESULT_MESSAGES{
    {Result::WIN, "You won!"},
    {Result::LOSE, "You lost :("},
    {Result::TIE, "A tie -_-"},
};

}

void ScoreView::build() {
    m_textLabel
    .center()
    .align(lvgl::Align::Center, 0, 0)
    .set_text(std::format("{}", RESULT_MESSAGES[m_result]))
    .style()
    .text_font(lvgl::Font::montserrat_20());

    m_returnButton
    .align(lvgl::Align::Center, 0, 40)
    .on_click([this] (lvgl::Event&) {
        m_screen.setView(View::MENU);
    });
    
    m_returnLabel
    .align(lvgl::Align::Center)
    .set_text("Return to menu");
}