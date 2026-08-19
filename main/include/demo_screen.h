#pragma once

#include "base_screen.h"

class DemoScreen : public BaseScreen {
    protected:
    virtual void construct(void) override {
        screen_.style().bg_color(lvgl::Color::from_hex(0x101820));

        title_.set_text("ESP32-S3 + LVGL C++ WRAPPER")
            .align(lvgl::Align::Center, 0, -25)
            .style()
            .text_color(lvgl::Color::from_hex(0xFFFFFF))
            .text_font(lvgl::Font::montserrat_14());

        status_.set_text("Display initialized successfully")
            .align(lvgl::Align::Center, 0, 18)
            .style()
            .text_color(lvgl::Color::from_hex(0x35D07F));
    }
};
