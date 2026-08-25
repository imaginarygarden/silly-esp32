#ifndef SHOWCASE_VIEW_H
#define SHOWCASE_VIEW_H

#include "ui/view.h"

class ShowcaseView : public View {
    int m_counter{};

    lvgl::Button m_titleButton;
    lvgl::Label m_titleLabel;
    lvgl::Label m_status;
    lvgl::Button m_decrementButton;
    lvgl::Button m_incrementButton;
    lvgl::Label m_decrementLabel;
    lvgl::Label m_incrementLabel;
    lvgl::Label m_counterLabel;
    lvgl::Slider m_slider;
    lvgl::Label m_sliderLabel;
    lvgl::Bar m_progress;
    lvgl::Checkbox m_checkbox;
    lvgl::Switch m_toggle;
    lvgl::Label m_toggleLabel;

    void configure_counter();
    void configure_slider();
    void configure_toggles();
    void update_counter();
    void construct();

public:
    ShowcaseView(lvgl::Object &parent) : View{parent} {}
    void build() override;
};

#endif