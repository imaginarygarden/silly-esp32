#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "ui/component/button.h"
#include "ui/view.h"

class MenuView final : public View {
    std::vector<std::unique_ptr<Button>> m_gameButtons{};

    lvgl::TabView m_tabView{m_parent};
    lvgl::TabPage m_gamesPage{m_tabView.add_tab("Games")};
    lvgl::TabPage m_leaderboardPage{m_tabView.add_tab("Leaderboard")};
    lvgl::TabPage m_settingsPage{m_tabView.add_tab("Settings")};
    lvgl::Label m_leaderboardLabel{m_leaderboardPage};
    lvgl::Label m_settingsLabel{m_settingsPage};

   public:
    MenuView(lvgl::Object& parent) : View{parent} {}
    void build() override;
};

#endif