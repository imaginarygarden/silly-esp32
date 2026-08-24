#ifndef VIEW_HOST_H
#define VIEW_HOST_H

#include "ui/view.h"

#include "lvgl_cpp.h"

class Controller;
struct State;
struct Error;
enum class Result;
enum class Route;
enum class GameRoute;

class ViewHost {
protected:
    Controller &m_controller;
    State &m_state;
    lvgl::Object m_screen{lvgl::Screen::active()};
    std::unique_ptr<View> m_currentView{};

public:
    ViewHost(Controller &controller);

    void reset();
    void update();
    void throwError(Error error);
    void requestView(Route view);
    void setView(Route view);
    void setGame(GameRoute game);
    void runGame();
    void endGame(Result result);
    State &getState() const;
    lvgl::Object &get();
};

#endif