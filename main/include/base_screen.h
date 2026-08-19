#pragma once

#include "esp_lvgl_port.h"
#include "lvgl_cpp.h"

class BaseScreen {
public:
    BaseScreen()
        : screen_(lvgl::Screen::active()), title_(screen_), status_(screen_)
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

    lvgl::Screen screen_;
    lvgl::Label title_;
    lvgl::Label status_;
};