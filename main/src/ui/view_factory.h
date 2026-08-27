#ifndef VIEW_FACTORY_H
#define VIEW_FACTORY_H

#include <memory>

#include "app/error.h"
#include "game/game_result.h"
#include "ui/view.h"

class ViewFactory final {
    ViewFactory() {}

   public:
    static ViewFactory& instance();

    [[nodiscard]]
    std::function<std::unique_ptr<View>()> menu(lvgl::Object& parent);

    [[nodiscard]]
    std::function<std::unique_ptr<View>()> error(lvgl::Object& parent,
                                                 const Error error);

    [[nodiscard]]
    std::function<std::unique_ptr<View>()> score(lvgl::Object& parent,
                                                 const GameResult result);

    [[nodiscard]]
    std::function<std::unique_ptr<View>()> description(
        lvgl::Object& parent, std::string_view name,
        std::string_view description);
};

#endif