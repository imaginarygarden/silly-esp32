#include "ui/view_host.h"
#include "game/game.h"
#include "game/sequence/sequence_game.h"
#include "app/controller.h"
#include "enum/game_route.h"
#include "ui/view/menu_view.h"
#include "ui/view/game_view.h"
#include "ui/view/showcase_view.h"
#include "ui/view/score_view.h"
#include "ui/view/description_view.h"
#include "ui/view/error_view.h"

#include "esp_lvgl_port.h"

#include <unordered_map>

ViewHost::ViewHost(Controller &controller) : m_controller{controller}, m_state{m_controller.getState()}
{
    requestView(Route::MENU);
}

void ViewHost::reset() {
    m_screen.clean();
    m_screen.style()
            .bg_color(lvgl::Color::from_hex(0xFFFFFF));
}

void ViewHost::update() {
    if (lvgl_port_lock(0)) {
        if (m_state.nextView && (!m_currentView || m_state.currentView != *m_state.nextView)) {
            Route requested = *m_state.nextView;
            m_state.nextView.reset();
            setView(requested);
        }

        if (m_currentView)
            m_currentView->update();

        lvgl_port_unlock();
    }
}

void ViewHost::throwError(Error error) {
    m_state.error = error;
    requestView(Route::ERROR);
}

void ViewHost::requestView(Route view) {
    m_state.nextView.emplace(view);
}

void ViewHost::setView(Route view) {
    if (m_currentView)
        m_currentView->onExit();

    reset();

    switch (view) {
        case Route::MENU:
            m_currentView = std::make_unique<MenuView>(*this);
            break;
        case Route::DEMO:
            m_currentView = std::make_unique<ShowcaseView>(*this);
            break;
        case Route::GAME:
            m_currentView = std::make_unique<GameView>(*this);
            break;
        case Route::SCORE:
            m_currentView = std::make_unique<ScoreView>(*this);
            break;
        case Route::DESCRIPTION:
            m_currentView = std::make_unique<DescriptionView>(*this);
            break;
        case Route::ERROR:
        default:
            m_currentView = std::make_unique<ErrorView>(*this);
    }

    m_state.currentView = view;
    m_currentView->build();
}

void ViewHost::setGame(GameRoute game) {
    switch (game) {
        case GameRoute::SEQUENCE:
            m_state.game = std::make_unique<SequenceGame>(*this);
            break;
        default:
            throwError(Error{"Requested game does not exist."});
            return;
    }

    requestView(Route::DESCRIPTION);
}

void ViewHost::runGame() {
    if (!m_state.game)
        return;

    m_state.game->run();
    requestView(Route::GAME);
}

void ViewHost::endGame(Result result) {
    if (!m_state.game)
        return;

    m_state.result = result;
    requestView(Route::SCORE);
}

State &ViewHost::getState() const {
    return m_state;
}

lvgl::Object &ViewHost::get() {
    return m_screen;
}