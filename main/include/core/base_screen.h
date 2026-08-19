#pragma once

#include "esp_lvgl_port.h"
#include "lvgl_cpp.h"

class BaseScreen {
public:
    BaseScreen()
    {
    }

    void render(void) {
        if (lvgl_port_lock(0)) {
            construct();
            lvgl_port_unlock();
        }
    }

protected:
    virtual void construct(void) = 0;

    lvgl::Screen m_screen{lvgl::Screen::active()};
    lvgl::Label m_title{m_screen};
    lvgl::Label m_status{m_screen};
};