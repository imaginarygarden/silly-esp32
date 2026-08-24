#ifndef STATE_H
#define STATE_H

#include "enum/route.h"
#include "interface/igame.h"
#include "app/error.h"

#include <optional>

struct State {
    bool active{true};
};

#endif