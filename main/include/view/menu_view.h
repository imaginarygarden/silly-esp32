#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "base/base_view.h"
#include "base/base_screen.h"

class MenuView : public BaseView {
    lvgl::TabView m_tabView{m_screen.get()};
    lvgl::TabPage m_gamesPage{m_tabView.add_tab("Games")};
    lvgl::TabPage m_leaderboardPage{m_tabView.add_tab("Leaderboard")};
    lvgl::TabPage m_settingsPage{m_tabView.add_tab("Settings")};
    lvgl::Button m_testButton{m_gamesPage};
    lvgl::Label m_testButtonLabel{m_testButton};
    lvgl::Label m_leaderboardLabel{m_leaderboardPage};
    lvgl::Label m_settingsLabel{m_settingsPage};

public:
    MenuView(BaseScreen &screen) : BaseView{screen}
    {
    }

    void build() override;
};

#endif