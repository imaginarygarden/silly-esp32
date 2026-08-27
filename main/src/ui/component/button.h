#ifndef BUTTON_H
#define BUTTON_H

#include "lvgl_cpp.h"

class Button {
    lvgl::Object &m_parent;
    lvgl::Button m_button{m_parent};
    lvgl::Label m_label{m_button};

   public:
    Button(lvgl::Object &parent) : m_parent{parent} {}

    lvgl::Button &get() { return m_button; }
    lvgl::Label &get_label() { return m_label; }
};

#endif