#include "ui/view/score_view.h"
#include "app/state.h"
#include "app/error.h"
#include "enum/result.h"

#include <unordered_map>

namespace {

std::unordered_map<Result, std::string> RESULT_MESSAGES{
    {Result::WIN, "You won!"},
    {Result::LOSE, "You lost :("},
    {Result::TIE, "A tie -_-"},
};

}

void ScoreView::build() {
    if (!m_screen.getState().result.has_value())
        m_screen.throwError(Error{"Last result is not available."});

    m_textLabel
    .center()
    .align(lvgl::Align::Center, 0, 0)
    .set_text(std::format("{}", RESULT_MESSAGES[*m_screen.getState().result]))
    .style()
    .text_font(lvgl::Font::montserrat_20());

    m_returnButton
    .align(lvgl::Align::Center, 0, 40)
    .on_click([this] (lvgl::Event&) {
        m_screen.requestView(Route::MENU);
    });
    
    m_returnLabel
    .align(lvgl::Align::Center)
    .set_text("Return to menu");
}