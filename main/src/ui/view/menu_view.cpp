#include "ui/view/menu_view.h"

#include "app/command.h"
#include "game/game_factory.h"
#include "game/game_route.h"
#include "misc/enums.h"

void MenuView::build() {
    m_tabView = lvgl::TabView{m_parent};
    m_gamesPage = lvgl::TabPage{m_tabView.add_tab("Games")};
    m_leaderboardPage = lvgl::TabPage{m_tabView.add_tab("Leaderboard")};
    m_settingsPage = lvgl::TabPage{m_tabView.add_tab("Settings")};
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

    for (auto descriptor : GameFactory::instance().descriptors()) {
        auto button = std::make_unique<Button>(m_gamesPage);

        button->get()
            .align(lvgl::Align::Center, 0, m_gameButtons.size() * 30)
            .on_click([this](lvgl::Event &) {
                _push_command(DescriptionNavigation{GameRoute::SEQUENCE});
            });

        button->get_label()
            .set_text(descriptor.name)
            .align(lvgl::Align::Center);

        m_gameButtons.push_back(std::move(button));
    }
}