#include "ui/view_factory.h"
#include "ui/view/menu_view.h"
#include "ui/view/error_view.h"
#include "ui/view/score_view.h"
#include "ui/view/showcase_view.h"
#include "ui/view/description_view.h"

std::unique_ptr<View> ViewFactory::create_menu(lvgl::Object &parent) {
    return std::make_unique<MenuView>(parent);
}

std::unique_ptr<View> ViewFactory::create_error(lvgl::Object &parent, Error error) {
    return std::make_unique<ErrorView>(parent, error);
}

std::unique_ptr<View> ViewFactory::create_score(lvgl::Object &parent, Result result) {
    return std::make_unique<ScoreView>(parent, result);
}

std::unique_ptr<View> ViewFactory::create_showcase(lvgl::Object &parent) {
    return std::make_unique<ShowcaseView>(parent);
}

std::unique_ptr<View> ViewFactory::create_description(lvgl::Object &parent, std::string name, std::string description) {
    return std::make_unique<DescriptionView>(parent, name, description);
}