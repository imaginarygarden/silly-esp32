#ifndef BASE_GAME_H
#define BASE_GAME_H

#include "base/base_view.h"

#include <string>

class BaseGame {
protected:
    BaseScreen &m_screen;

public:
    BaseGame(BaseScreen &screen) : m_screen{screen}
    {
    }

    virtual void build() = 0;
    
    virtual void update() = 0;

    virtual void run() = 0;

    virtual std::string getName() const { return "Dummy"; }

    virtual std::string getDescription() const { return "Just a simple game :)"; }
};

#endif