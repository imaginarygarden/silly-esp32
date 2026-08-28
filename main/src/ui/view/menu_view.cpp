#include "ui/view/menu_view.h"

#include "app/command.h"
#include "game/game_factory.h"
#include "misc/enums.h"

void MenuView::build() {
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
            .on_click([this, descriptor](lvgl::Event &) {
                _push_command(GameDescriptionNavigation{descriptor.route});
            });

        button->get_label().set_text(std::string{descriptor.name}.c_str());

        m_gameButtons.push_back(std::move(button));
    }
}