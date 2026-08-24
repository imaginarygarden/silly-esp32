#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "ui/view.h"
#include "ui/view_host.h"
#include "game/game.h"

class GameView : public View {
public:
    GameView(ViewHost &screen) : View{screen}
    {
    }

    void build() override {
        if (!m_screen.getState().game)
            m_screen.throwError(Error{"Game is not active."});
        else
            m_screen.getState().game->build();
    }

    void update() override {
        if (!m_screen.getState().game)
            m_screen.throwError(Error{"Game is not active."});
        else
            m_screen.getState().game->update();
    }
};

#endif