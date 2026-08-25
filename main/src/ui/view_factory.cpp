#include "ui/view_factory.h"

#include "ui/view/description_view.h"
#include "ui/view/error_view.h"
#include "ui/view/menu_view.h"
#include "ui/view/score_view.h"
#include "ui/view/showcase_view.h"

std::function<std::unique_ptr<View>()> ViewFactory::create_menu(
    lvgl::Object& parent) {
    return [&parent] { return std::make_unique<MenuView>(parent); };
}

std::function<std::unique_ptr<View>()> ViewFactory::create_error(
    lvgl::Object& parent, Error error) {
    return [&parent, &error] {
        return std::make_unique<ErrorView>(parent, error);
    };
}

std::function<std::unique_ptr<View>()> ViewFactory::create_score(
    lvgl::Object& parent, GameResult result) {
    return [&parent, &result] {
        return std::make_unique<ScoreView>(parent, result);
    };
}

std::function<std::unique_ptr<View>()> ViewFactory::create_showcase(
    lvgl::Object& parent) {
    return [&parent] { return std::make_unique<ShowcaseView>(parent); };
}

std::function<std::unique_ptr<View>()> ViewFactory::create_description(
    lvgl::Object& parent, std::string name, std::string description) {
    return [&parent, &name, &description] {
        return std::make_unique<DescriptionView>(parent, name, description);
    };
}