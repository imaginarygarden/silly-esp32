#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "ui/view.h"

class MenuView : public View {
    lvgl::TabView m_tabView;
    lvgl::TabPage m_gamesPage;
    lvgl::TabPage m_leaderboardPage;
    lvgl::TabPage m_settingsPage;
    lvgl::Button m_testButton;
    lvgl::Label m_testButtonLabel;
    lvgl::Label m_leaderboardLabel;
    lvgl::Label m_settingsLabel;

   public:
    MenuView(lvgl::Object& parent) : View{parent} {}
    void build() override;
};

#endif