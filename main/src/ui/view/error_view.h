#ifndef ERROR_VIEW_H
#define ERROR_VIEW_H

#include "app/error.h"
#include "ui/view.h"

class ErrorView final : public View {
    const Error m_error;

    lvgl::Label m_label{m_parent};

   public:
    ErrorView(lvgl::Object& parent, const Error error)
        : View{parent}, m_error{error} {}
    void build() override;
};

#endif