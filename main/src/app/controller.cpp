#include "app/controller.h"

#include "app/command.h"
#include "esp_lvgl_port.h"
#include "ui/view_factory.h"

void Controller::_input(const MenuNavigation data) {
    m_host.set_view(ViewFactory::instance().menu(m_host.screen()));
}

void Controller::_input(const ErrorNavigation data) {
    m_host.set_view(ViewFactory::instance().error(m_host.screen(), data.error));
}

void Controller::_input(const GameDescriptionNavigation data) {
    if (!m_session.set(data.route)) {
        m_host.set_view(ViewFactory::instance().error(
            m_host.screen(),
            Error{ErrorType::UNEXPECTED, "Could not set up the game."}));
        return;
    }

    auto descriptor = m_session.descriptor();

    if (!descriptor) {
        m_host.set_view(ViewFactory::instance().error(
            m_host.screen(),
            Error{ErrorType::UNEXPECTED, "Could not fetch game description."}));
        return;
    }

    m_host.set_view(ViewFactory::instance().description(
        m_host.screen(), descriptor->name, descriptor->description));
}
void Controller::_input(const GameScoreNavigation data) {
    m_host.set_view(
        ViewFactory::instance().score(m_host.screen(), data.result));
    m_session.reset();
}

void Controller::_input(const GameStartCommand data) {
    auto view = m_session.start(m_host.screen());

    if (!view) {
        m_host.set_view(ViewFactory::instance().error(
            m_host.screen(),
            Error{ErrorType::UNEXPECTED, "The game failed to start."}));
        return;
    }

    m_host.set_view(view);
}

void Controller::init() {
    if (lvgl_port_lock(0)) {
        m_host.set_view(ViewFactory::instance().menu(m_host.screen()));

        lvgl_port_unlock();
    }
}

void Controller::update() {
    if (lvgl_port_lock(0)) {
        while (auto command = m_host.poll_command()) input(*command);

        if (auto result = m_session.update())
            _input(GameScoreNavigation{*result});

        m_host.update_view();

        lvgl_port_unlock();
    }
}

void Controller::input(const Command command) {
    std::visit([this](auto&& value) { _input(std::move(value)); },
               std::move(command));
}

bool Controller::active() const { return m_active; }