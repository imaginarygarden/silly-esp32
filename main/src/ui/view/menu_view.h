#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "ui/component/button.h"
#include "ui/view.h"

class MenuView : public View {
    lvgl::TabView m_tabView;
    lvgl::TabPage m_gamesPage;
    lvgl::TabPage m_leaderboardPage;
    lvgl::TabPage m_settingsPage;
    lvgl::Label m_leaderboardLabel;
    lvgl::Label m_settingsLabel;

    std::vector<std::unique_ptr<Button>> m_gameButtons{};

   public:
    MenuView(lvgl::Object& parent) : View{parent} {}
    void build() override;
};

#endif