#pragma once

#include "base_screen.h"

class ShowcaseScreen : public BaseScreen {
public:
    ShowcaseScreen()
        : decrement_button_(screen_), increment_button_(screen_),
          decrement_label_(decrement_button_), increment_label_(increment_button_),
          counter_label_(screen_), slider_(screen_), slider_label_(screen_),
          progress_(screen_), checkbox_(screen_, "Enable option"),
          toggle_(screen_), toggle_label_(screen_)
    {
    }

protected:
    void construct() override
    {
        screen_.style().bg_color(lvgl::Color::from_hex(0x101820));

        title_.set_text("LVGL C++ Widget Showcase")
            .align(lvgl::Align::TopMid, 0, 8)
            .style()
            .text_color(lvgl::Color::from_hex(0xFFFFFF))
            .text_font(lvgl::Font::montserrat_14());

        configure_counter();
        configure_slider();
        configure_toggles();

        status_.set_text("Try the controls")
            .align(lvgl::Align::BottomMid, 0, -7)
            .style()
            .text_color(lvgl::Color::from_hex(0x35D07F));
    }

private:
    void configure_counter()
    {
        decrement_button_.set_size(70, 42)
            .align(lvgl::Align::Center, -90, -55)
            .on_clicked([this](lvgl::Event&) {
                --counter_;
                update_counter();
            });
        decrement_button_.style()
            .bg_color(lvgl::Color::from_hex(0xC94C4C))
            .radius(8);
        decrement_label_.set_text("-").center();

        counter_label_.set_text("0")
            .align(lvgl::Align::Center, 0, -55)
            .style()
            .text_color(lvgl::Color::from_hex(0xFFFFFF))
            .text_font(lvgl::Font::montserrat_14());

        increment_button_.set_size(70, 42)
            .align(lvgl::Align::Center, 90, -55)
            .on_clicked([this](lvgl::Event&) {
                ++counter_;
                update_counter();
            });
        increment_button_.style()
            .bg_color(lvgl::Color::from_hex(0x2878C8))
            .radius(8);
        increment_label_.set_text("+").center();
    }

    void configure_slider()
    {
        slider_.set_range(0, 100)
            .set_value(40)
            .set_size(235, 18)
            .align(lvgl::Align::Center, 0, 0)
            .on_value_changed([this](lvgl::Event&) {
                const int value = slider_.get_value();
                progress_.set_value(value);
                slider_label_.set_text_fmt("Level: %d%%", value);
            });

        slider_label_.set_text("Level: 40%")
            .align(lvgl::Align::Center, 0, -20)
            .style()
            .text_color(lvgl::Color::from_hex(0xD5DEE8));

        progress_.set_range(0, 100)
            .set_value(40)
            .set_size(235, 7)
            .align(lvgl::Align::Center, 0, 25);
        progress_.style(lvgl::Part::Indicator)
            .bg_color(lvgl::Color::from_hex(0x35D07F));
    }

    void configure_toggles()
    {
        checkbox_.align(lvgl::Align::Center, -72, 58)
            .on_value_changed([this](lvgl::Event&) {
                status_.set_text(
                    checkbox_.has_state(lvgl::State::Checked)
                        ? "Checkbox enabled"
                        : "Checkbox disabled");
            });
        checkbox_.style().text_color(lvgl::Color::from_hex(0xFFFFFF));

        toggle_.set_size(48, 25)
            .align(lvgl::Align::Center, 78, 58)
            .on_value_changed([this](lvgl::Event&) {
                toggle_label_.set_text(
                    toggle_.has_state(lvgl::State::Checked) ? "ON" : "OFF");
            });

        toggle_label_.set_text("OFF")
            .align(lvgl::Align::Center, 125, 58)
            .style()
            .text_color(lvgl::Color::from_hex(0xFFFFFF));
    }

    void update_counter()
    {
        counter_label_.set_text_fmt("%d", counter_);
        status_.set_text("Button clicked");
    }

    int counter_ = 0;
    lvgl::Button decrement_button_;
    lvgl::Button increment_button_;
    lvgl::Label decrement_label_;
    lvgl::Label increment_label_;
    lvgl::Label counter_label_;
    lvgl::Slider slider_;
    lvgl::Label slider_label_;
    lvgl::Bar progress_;
    lvgl::Checkbox checkbox_;
    lvgl::Switch toggle_;
    lvgl::Label toggle_label_;
};
