#ifndef DESCRIPTION_VIEW_H
#define DESCRIPTION_VIEW_H

#include "ui/view.h"

#include <string>

class DescriptionView : public View {
    std::string m_name;
    std::string m_description;

    lvgl::Label m_nameLabel;
    lvgl::Label m_descriptionLabel;
    lvgl::Button m_button;
    lvgl::Label m_buttonLabel;

public:
    DescriptionView(lvgl::Object &parent, std::string name, std::string description) : View{parent}, m_name{name}, m_description{description} {}
    void build() override;
};

#endif