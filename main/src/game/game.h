#ifndef GAME_H
#define GAME_H

#include "game/game_status.h"

#include <string>

class Game {
public:
    virtual ~Game() = default;
    virtual GameStatus update() = 0;
    virtual void start() = 0;
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
};

#endif