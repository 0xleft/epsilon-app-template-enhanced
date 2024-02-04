#ifndef EXAMPLE_WINDOWS_H
#define EXAMPLE_WINDOWS_H

#include "eadkpp.h"
#include "game.h"
#include "palette.h"

namespace example
{
namespace windows
{

enum class WindowType {
    GAME,
    MENU,
    PAUSE
};

class Window {
private:
    WindowType windowType = WindowType::MENU;
    game::Game* game = new game::Game();

    void runGameWindow();
    void runMenuWindow();
    void runPauseWindow();
public:
// wtf cannot have this in windows.cpp
    template<WindowType type>
    void runWindow() {
        switch (type) {
        case WindowType::GAME:
            runGameWindow();
            break;
        case WindowType::MENU:
            runMenuWindow();
            break;
        case WindowType::PAUSE:
            runPauseWindow();
            break;
        }
    }

    ~Window() { delete this->game; }
};

} // namespace windows
} // namespace example

#endif