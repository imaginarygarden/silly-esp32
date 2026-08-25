#include "app/controller.h"
#include "app/command.h"
#include "ui/view_factory.h"

#include "esp_lvgl_port.h"

void Controller::init() {
    if (lvgl_port_lock(0)) {

        m_screen.set_view(ViewFactory::instance().create_menu(m_screen));

        lvgl_port_unlock();
    }
}

void Controller::update() {
    if (lvgl_port_lock(0)) {

        while (auto command = m_screen.poll_command())
            handle_command(*command);

        if (auto result = m_session.update())
            handle_command(ScoreNavigation{*result});

        m_screen.update_view();

        lvgl_port_unlock();
    }
}

void Controller::handle_command(Command command) {
    std::visit([this](auto&& value) {
        handle_command(std::move(value));
    }, std::move(command));
}

void Controller::handle_command(MenuNavigation data) {
    m_screen.set_view(ViewFactory::instance().create_menu(m_screen));
}

void Controller::handle_command(ErrorNavigation data) {
    m_screen.set_view(ViewFactory::instance().create_error(m_screen, data.error));
}

void Controller::handle_command(DescriptionNavigation data) {
    if (!m_session.set(data.route)) {
        m_screen.set_view(ViewFactory::instance().create_error(m_screen, Error{ErrorType::UNEXPECTED, "Could not set up the game."}));
        return;
    }

    m_screen.set_view(ViewFactory::instance().create_description(m_screen, *m_session.name(), *m_session.description()));
}
void Controller::handle_command(ScoreNavigation data) {
    m_screen.set_view(ViewFactory::instance().create_score(m_screen, data.result));
    m_session.reset();
}

void Controller::handle_command(StartCommand data) {
    std::function<std::unique_ptr<View>()> view = m_session.start(m_screen);

    if (!view) {
        m_screen.set_view(ViewFactory::instance().create_error(m_screen, Error{ErrorType::UNEXPECTED, "The game failed to start."}));
        return;
    }

    m_screen.set_view(view);
}