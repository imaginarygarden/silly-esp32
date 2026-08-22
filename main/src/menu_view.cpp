#include "view/menu_view.h"

void MenuView::build() {
    m_leaderboardLabel
    .center()
    .align(lvgl::Align::Center)
    .set_text("Under construction")
    .style()
    .text_font(lvgl::Font::montserrat_20());

    m_settingsLabel
    .center()
    .align(lvgl::Align::Center)
    .set_text("Under construction")
    .style()
    .text_font(lvgl::Font::montserrat_20())
    ;

    m_testButton.center().set_size(60, 40)
    .on_click([this] (lvgl::Event&) {
        m_screen.setGame(Game::SEQUENCE);
    })
    ;
    m_testButtonLabel.set_text("Test").align(lvgl::Align::Center, 0, 0);
}