#include "base/base_screen.h"
#include "base/base_game.h"
#include "base/base_error.h"
#include "core/controller.h"
#include "core/templates.h"
#include "view/menu_view.h"
#include "view/game_view.h"
#include "view/showcase_view.h"
#include "view/score_view.h"
#include "view/description_view.h"
#include "game/sequence_game.h"

#include "esp_lvgl_port.h"

#include <unordered_map>

namespace {

using ViewFactory = Factory<BaseView, BaseScreen&>;

template <class Derived>
auto createView = create<BaseView, Derived, BaseScreen&>;

std::unordered_map<View, ViewFactory> VIEW_FACTORIES{
    {View::MENU, createView<MenuView>},
    {View::DEMO, createView<ShowcaseView>},
    {View::DESCRIPTION, createView<DescriptionView>},
};

using GameFactory = Factory<BaseGame, BaseScreen&>;

template <class Derived>
auto createGame = create<BaseGame, Derived, BaseScreen&>;

std::unordered_map<Game, GameFactory> GAME_FACTORIES{
    {Game::SEQUENCE, createGame<SequenceGame>},
};

auto createError = create<BaseView, BaseError, BaseScreen&, std::string>;
auto createScore = create<BaseView, ScoreView, BaseScreen&, Result>;
auto createGameView = create<BaseView, GameView, BaseScreen&, BaseGame*>;

}

void BaseScreen::reset() {
    m_screen.clean();
    m_screen.style()
            .bg_color(lvgl::Color::from_hex(0xFFFFFF));
}

void BaseScreen::update() {
    if (m_currentView)
        m_currentView->update();
}

void BaseScreen::setView(View view) {
    if (m_currentView)
        m_currentView->onExit();

    reset();

    State &state = m_controller.getState();

    switch (view) {
        case View::GAME:
            m_currentView = state.game ? createGameView(*this, state.game.get()) : createError(*this, "Game is not active.");
            break;
        case View::SCORE:
            m_currentView = state.game ? createScore(*this, state.lastResult) : createError(*this, "Game is not active.");
            break;
        default:
            m_currentView = VIEW_FACTORIES[view](*this);
    }

    m_currentView->build();
}

void BaseScreen::setGame(Game game) {
    State &state = m_controller.getState();

    state.game = GAME_FACTORIES[game](*this);
    setView(View::DESCRIPTION);
}

void BaseScreen::runGame() {
    State &state = m_controller.getState();

    if (!state.game)
        return;

    state.game->run();
    setView(View::GAME);
}

void BaseScreen::endGame(Result result) {
    State &state = m_controller.getState();

    if (!state.game)
        return;

    state.lastResult = result;
    setView(View::SCORE);
}

State &BaseScreen::getState() const {
    return m_controller.getState();
}

lvgl::Object &BaseScreen::get() {
    return m_screen;
}