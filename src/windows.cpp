#include "windows.h"

namespace example
{
namespace windows
{

void Window::runGameWindow() {
    this->game->run();

    delete game;
    game = new game::Game();

    runWindow<WindowType::MENU>();
}

void Window::runMenuWindow() {
    EADK::Display::clear(Black);
    
    while (true) {
        EADK::Keyboard::State kbd = EADK::Keyboard::scan();
        if (kbd.keyDown(EADK::Keyboard::Key::EXE)) {
            break;
        }
        if (kbd.keyDown(EADK::Keyboard::Key::Back)) {
            return;
        }
        EADK::Timing::msleep(10);
    }

    runWindow<WindowType::GAME>();
}

void Window::runPauseWindow() {
    while (true) {
        EADK::Keyboard::State kbd = EADK::Keyboard::scan();
        if (kbd.keyDown(EADK::Keyboard::Key::EXE)) {
            break;
        }
        EADK::Timing::msleep(10);
    }

    runWindow<WindowType::GAME>();
}

} // namespace windows
} // namespace battlezone