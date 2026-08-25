#include "ui/view/showcase_view.h"

void ShowcaseView::configure_counter() {
    m_decrementButton.set_size(70, 42)
        .align(lvgl::Align::Center, -90, -55)
        .on_clicked([this](lvgl::Event&) {
            --m_counter;
            update_counter();
        });
    m_decrementButton.style()
        .bg_color(lvgl::Color::from_hex(0xC94C4C))
        .radius(8);
    m_decrementLabel.set_text("-").center();

    m_counterLabel.set_text("0")
        .align(lvgl::Align::Center, 0, -55)
        .style()
        .text_color(lvgl::Color::from_hex(0xFFFFFF))
        .text_font(lvgl::Font::montserrat_14());

    m_incrementButton.set_size(70, 42)
        .align(lvgl::Align::Center, 90, -55)
        .on_clicked([this](lvgl::Event&) {
            ++m_counter;
            update_counter();
        });
    m_incrementButton.style()
        .bg_color(lvgl::Color::from_hex(0x2878C8))
        .radius(8);
    m_incrementLabel.set_text("+").center();
}

void ShowcaseView::configure_slider() {
    m_slider.set_range(0, 100)
        .set_value(40)
        .set_size(235, 18)
        .align(lvgl::Align::Center, 0, 0)
        .on_value_changed([this](lvgl::Event&) {
            const int value = m_slider.get_value();
            m_progress.set_value(value);
            m_sliderLabel.set_text_fmt("Level: %d%%", value);
        });

    m_sliderLabel.set_text("Level: 40%")
        .align(lvgl::Align::Center, 0, -20)
        .style()
        .text_color(lvgl::Color::from_hex(0xD5DEE8));

    m_progress.set_range(0, 100).set_value(40).set_size(235, 7).align(
        lvgl::Align::Center, 0, 25);
    m_progress.style(lvgl::Part::Indicator)
        .bg_color(lvgl::Color::from_hex(0x35D07F));
}

void ShowcaseView::configure_toggles() {
    m_checkbox.align(lvgl::Align::Center, -72, 58)
        .on_value_changed([this](lvgl::Event&) {
            m_status.set_text(m_checkbox.has_state(lvgl::State::Checked)
                                  ? "Checkbox enabled"
                                  : "Checkbox disabled");
        });
    m_checkbox.style().text_color(lvgl::Color::from_hex(0xFFFFFF));

    m_toggle.set_size(48, 25)
        .align(lvgl::Align::Center, 78, 58)
        .on_value_changed([this](lvgl::Event&) {
            m_toggleLabel.set_text(
                m_toggle.has_state(lvgl::State::Checked) ? "ON" : "OFF");
        });

    m_toggleLabel.set_text("OFF")
        .align(lvgl::Align::Center, 125, 58)
        .style()
        .text_color(lvgl::Color::from_hex(0xFFFFFF));
}

void ShowcaseView::update_counter() {
    m_counterLabel.set_text_fmt("%d", m_counter);
    m_status.set_text("Button clicked");
}

void ShowcaseView::construct() {
    m_titleButton = lvgl::Button{m_parent};
    m_titleLabel = lvgl::Label{m_titleButton};
    m_status = lvgl::Label{m_parent};
    m_decrementButton = lvgl::Button{m_parent};
    m_incrementButton = lvgl::Button{m_parent};
    m_decrementLabel = lvgl::Label{m_decrementButton};
    m_incrementLabel = lvgl::Label{m_incrementButton};
    m_counterLabel = lvgl::Label{m_parent};
    m_slider = lvgl::Slider{m_parent};
    m_sliderLabel = lvgl::Label{m_parent};
    m_progress = lvgl::Bar{m_parent};
    m_checkbox = lvgl::Checkbox{m_parent, "Enable option"};
    m_toggle = lvgl::Switch{m_parent};
    m_toggleLabel = lvgl::Label{m_parent};

    m_parent.style().bg_color(lvgl::Color::black());

    m_titleButton.align(lvgl::Align::TopMid, 0, 8)
        .set_size(60, 40)
        .on_click([this](lvgl::Event&) { push_command(MenuNavigation{}); });

    m_titleLabel.set_text("Go back <-")
        .align(lvgl::Align::Center, 0, 0)
        .style()
        .text_color(lvgl::Color::from_hex(0xFFFFFF))
        .text_font(lvgl::Font::montserrat_14());

    configure_counter();
    configure_slider();
    configure_toggles();

    m_status.set_text("Try the controls")
        .align(lvgl::Align::BottomMid, 0, -7)
        .style()
        .text_color(lvgl::Color::from_hex(0x35D07F));
}

void ShowcaseView::build() { construct(); }