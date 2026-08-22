#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include "base/base_view.h"
#include "lvgl_cpp.h"

class Controller;
struct State;

enum class View {
    MENU,
    GAME,
    DEMO,
    SCORE,
    DESCRIPTION,
    INVITE_RESPONSE,
    INVITE_REQUEST,
};

enum class Game {
    SEQUENCE,
    REACTION,
    AIM,
};

enum class Result {
    WIN,
    LOSE,
    TIE,
    ERROR
};

class BaseScreen {
protected:
    Controller &m_controller;
    lvgl::Object m_screen{lvgl::Screen::active()};
    std::unique_ptr<BaseView> m_currentView{};

public:
    BaseScreen(Controller &controller) : m_controller{controller}
    {
        setView(View::MENU);
    }

    void reset();
    void update();
    void setView(View view);
    void setGame(Game game);
    void runGame();
    void endGame(Result result);
    State &getState() const;
    lvgl::Object &get();
};

#endif