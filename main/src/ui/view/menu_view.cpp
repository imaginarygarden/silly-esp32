#include "ui/view/menu_view.h"

#include "game/game_route.h"

void MenuView::build() {
    m_tabView = lvgl::TabView{m_parent};
    m_gamesPage = lvgl::TabPage{m_tabView.add_tab("Games")};
    m_leaderboardPage = lvgl::TabPage{m_tabView.add_tab("Leaderboard")};
    m_settingsPage = lvgl::TabPage{m_tabView.add_tab("Settings")};
    m_testButton = lvgl::Button{m_gamesPage};
    m_testButtonLabel = lvgl::Label{m_testButton};
    m_leaderboardLabel = lvgl::Label{m_leaderboardPage};
    m_settingsLabel = lvgl::Label{m_settingsPage};

    m_leaderboardLabel.center()
        .align(lvgl::Align::Center)
        .set_text("Under construction")
        .style()
        .text_font(lvgl::Font::montserrat_20());

    m_settingsLabel.center()
        .align(lvgl::Align::Center)
        .set_text("Under construction")
        .style()
        .text_font(lvgl::Font::montserrat_20());

    m_testButton.center().set_size(60, 40).on_click([this](lvgl::Event&) {
        push_command(DescriptionNavigation{GameRoute::SEQUENCE});
    });

    m_testButtonLabel.set_text("Test").align(lvgl::Align::Center, 0, 0);
}