#ifndef IGAME_H
#define IGAME_H

#include "enum/status.h"

#include <string>

class IGame {
public:
    virtual ~IGame() = default;

    virtual Status update() = 0;
    virtual void start() = 0;
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
};

#endif