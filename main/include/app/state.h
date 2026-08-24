#ifndef STATE_H
#define STATE_H

#include "enum/result.h"
#include "enum/route.h"
#include "game/game.h"
#include "app/error.h"

#include <optional>

struct State {
    std::unique_ptr<Game> game;
    std::optional<Result> result;
    std::optional<Route> nextView;
    std::optional<Error> error;
    Route currentView{Route::MENU};
    bool playing{false};
    bool active{true};
};

#endif