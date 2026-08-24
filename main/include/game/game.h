#ifndef GAME_H
#define GAME_H

#include "ui/view.h"

#include <string>

class Game {
protected:
    ViewHost &m_screen;

public:
    Game(ViewHost &screen) : m_screen{screen}
    {
    }

    virtual ~Game() = default;

    virtual void build() = 0;
    
    virtual void update() = 0;

    virtual void run() = 0;

    virtual std::string getName() const { return "Dummy"; }

    virtual std::string getDescription() const { return "Just a simple game :)"; }
};

#endif