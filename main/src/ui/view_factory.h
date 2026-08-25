#ifndef VIEW_FACTORY_H
#define VIEW_FACTORY_H

#include "ui/view.h"
#include "app/error.h"
#include "game/game_result.h"

#include <memory>

class ViewFactory {
    ViewFactory() {}

public:
    static ViewFactory &instance() { static ViewFactory object{}; return object; }
    std::function<std::unique_ptr<View>()> create_menu(lvgl::Object &parent);
    std::function<std::unique_ptr<View>()> create_error(lvgl::Object &parent, Error error);
    std::function<std::unique_ptr<View>()> create_score(lvgl::Object &parent, GameResult result);
    std::function<std::unique_ptr<View>()> create_showcase(lvgl::Object &parent);
    std::function<std::unique_ptr<View>()> create_description(lvgl::Object &parent, std::string name, std::string description);
};

#endif