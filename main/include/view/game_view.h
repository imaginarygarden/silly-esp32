#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "base/base_view.h"
#include "base/base_screen.h"
#include "base/base_game.h"

class GameView : public BaseView {
    BaseGame *m_game;

public:
    GameView(BaseScreen &screen, BaseGame *game) : BaseView{screen}, m_game{game}
    {
    }

    void build() override {
        if (m_game)
            m_game->build();
    }

    void update() override {
        if (m_game)
            m_game->update();
    }
};

#endif