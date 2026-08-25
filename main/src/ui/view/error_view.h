#ifndef ERROR_VIEW_H
#define ERROR_VIEW_H

#include "ui/view.h"
#include "app/error.h"

#include <string>
#include <format>

class ErrorView : public View {
    Error m_error;

    lvgl::Label m_label;

public:
    ErrorView(lvgl::Object &parent, Error error) : View{parent}, m_error{error} {}
    void build() override;
};

#endif