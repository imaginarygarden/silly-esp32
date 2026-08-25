#ifndef ERROR_VIEW_H
#define ERROR_VIEW_H

#include <format>
#include <string>

#include "app/error.h"
#include "ui/view.h"

class ErrorView : public View {
    Error m_error;

    lvgl::Label m_label;

   public:
    ErrorView(lvgl::Object& parent, Error error)
        : View{parent}, m_error{error} {}
    void build() override;
};

#endif