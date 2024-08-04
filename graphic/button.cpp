#include <graphic/button.h>
#include <main/controller.h>

Button::Button( std::string name, 
                SDL_Rect position, 
                SDL_Vector scaleRate,
                SDL_Vector velocity,
                SDL_Texture *texture
) : Graphic(name, position, scaleRate, velocity)
{
    this->buttonTexture = texture;
}

int Button::render() {
    if (!isActive()) {
        return 0;
    }

    if (!Controller::getInstance().render(buttonTexture, NULL, &position)) {
        return 1;
    }

    return Graphic::render();
}