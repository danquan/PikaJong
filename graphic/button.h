#ifndef __BUTTON_H
#define __BUTTON_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <graphic.h>

class Button : public Graphic {
private:
    SDL_Texture *buttonTexture;
public:
    Button(SDL_Texture *texture, std::string name, SDL_Rect position);

    /**
     * @brief Render the button
     * @return 0 if success
     */
    virtual int render();
};

#endif