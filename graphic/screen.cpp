#include <graphic/screen.h>
#include <main/controller.h>

Screen::Screen( std::string name, 
                SDL_Rect position, 
                SDL_Vector scaleRate,
                SDL_Vector velocity,
                SDL_Texture *background
) : Graphic(name, position, scaleRate, velocity)
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


