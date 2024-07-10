#include <screen.h>
#include <controller.h>

Screen::Screen(SDL_Texture *background, std::string name, SDL_Rect position) : Graphic(name, position)
{
    this->background = background;
}

int Screen::render() {
    if (!isActive()) {
        return 0;
    }

    if (!Controller::getInstance().render(background, NULL, &position)) {
        return 1;
    }

    return Graphic::render();
}


