#include "app/controller.h"

#include "app/command.h"
#include "esp_lvgl_port.h"
#include "game/game_factory.h"
#include "ui/view_factory.h"

void Controller::_input(MenuNavigation data) {
    m_screen.set_view(ViewFactory::instance().create_menu(m_screen));
}

void Controller::_input(ErrorNavigation data) {
    m_screen.set_view(
        ViewFactory::instance().create_error(m_screen, data.error));
}

void Controller::_input(DescriptionNavigation data) {
    if (!m_session.set(data.route)) {
        m_screen.set_view(ViewFactory::instance().create_error(
            m_screen,
            Error{ErrorType::UNEXPECTED, "Could not set up the game."}));
        return;
    }

    auto descriptor = GameFactory::instance().descriptor(data.route);

    if (!descriptor) {
        m_screen.set_view(ViewFactory::instance().create_error(
            m_screen,
            Error{ErrorType::UNEXPECTED, "Could not fetch game description."}));
        return;
    }

    m_screen.set_view(ViewFactory::instance().create_description(
        m_screen, descriptor->name, descriptor->description));
}
void Controller::_input(ScoreNavigation data) {
    m_screen.set_view(
        ViewFactory::instance().create_score(m_screen, data.result));
    m_session.reset();
}

void Controller::_input(StartCommand data) {
    std::function<std::unique_ptr<View>()> view = m_session.start(m_screen);

    if (!view) {
        m_screen.set_view(ViewFactory::instance().create_error(
            m_screen,
            Error{ErrorType::UNEXPECTED, "The game failed to start."}));
        return;
    }

    m_screen.set_view(view);
}

void Controller::init() {
    if (lvgl_port_lock(0)) {
        m_screen.set_view(ViewFactory::instance().create_menu(m_screen));

        lvgl_port_unlock();
    }
}

void Controller::update() {
    if (lvgl_port_lock(0)) {
        while (auto command = m_screen.poll_command()) input(*command);

        if (auto result = m_session.update()) _input(ScoreNavigation{*result});

        m_screen.update_view();

        lvgl_port_unlock();
    }
}

void Controller::input(Command command) {
    std::visit([this](auto&& value) { _input(std::move(value)); },
               std::move(command));
}