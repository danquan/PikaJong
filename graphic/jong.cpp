#include <jong.h>
#include <main/controller.h>

Jong::Jong(SDL_Texture *jong, std::string name, SDL_Rect position) : Graphic(name, position)
{
    this->jongTile = jong;
}

int Jong::render() {
    if (!isActive()) {
        return 0;
    }

    if (!Controller::getInstance().render(jongTile, NULL, &position)) {
        return 1;
    }

    return 0;
}