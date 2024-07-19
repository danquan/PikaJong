#include <button.h>
#include <main/controller.h>

Button::Button(SDL_Texture *texture, std::string name, SDL_Rect position) : Graphic(name, position)
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

    return 0;
}