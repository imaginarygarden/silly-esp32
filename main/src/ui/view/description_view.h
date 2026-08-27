#ifndef DESCRIPTION_VIEW_H
#define DESCRIPTION_VIEW_H

#include <string>

#include "ui/view.h"

class DescriptionView final : public View {
    std::string m_name;
    std::string m_description;

    lvgl::Label m_nameLabel{m_parent};
    lvgl::Label m_descriptionLabel{m_parent};
    lvgl::Button m_button{m_parent};
    lvgl::Label m_buttonLabel{m_button};

   public:
    DescriptionView(lvgl::Object& parent, std::string_view name,
                    std::string_view description)
        : View{parent}, m_name{name}, m_description{description} {}
    void build() override;
};

#endif