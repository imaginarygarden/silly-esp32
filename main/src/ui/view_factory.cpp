#include "ui/view_factory.h"

#include "ui/view/description_view.h"
#include "ui/view/error_view.h"
#include "ui/view/menu_view.h"
#include "ui/view/score_view.h"

ViewFactory& ViewFactory::instance() {
    static ViewFactory object{};
    return object;
}

std::function<std::unique_ptr<View>()> ViewFactory::menu(lvgl::Object& parent) {
    return [&parent] { return std::make_unique<MenuView>(parent); };
}

std::function<std::unique_ptr<View>()> ViewFactory::error(lvgl::Object& parent,
                                                          const Error error) {
    return
        [&parent, error] { return std::make_unique<ErrorView>(parent, error); };
}

std::function<std::unique_ptr<View>()> ViewFactory::score(
    lvgl::Object& parent, const GameResult result) {
    return [&parent, result] {
        return std::make_unique<ScoreView>(parent, result);
    };
}

std::function<std::unique_ptr<View>()> ViewFactory::description(
    lvgl::Object& parent, std::string_view name, std::string_view description) {
    return [&parent, name, description] {
        return std::make_unique<DescriptionView>(parent, name, description);
    };
}