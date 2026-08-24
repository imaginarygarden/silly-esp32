#ifndef VIEW_FACTORY_H
#define VIEW_FACTORY_H

#include "ui/view.h"
#include "app/error.h"
#include "enum/result.h"

#include <memory>

class ViewFactory {
    ViewFactory() {}

public:
    static ViewFactory &instance() { static ViewFactory object{}; return object; }

    std::unique_ptr<View> create_menu(lvgl::Object &parent);
    std::unique_ptr<View> create_error(lvgl::Object &parent, Error error);
    std::unique_ptr<View> create_score(lvgl::Object &parent, Result result);
    std::unique_ptr<View> create_showcase(lvgl::Object &parent);
    std::unique_ptr<View> create_description(lvgl::Object &parent, std::string name, std::string description);
};

#endif