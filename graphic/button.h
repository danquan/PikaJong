#ifndef __BUTTON_H
#define __BUTTON_H

#ifdef (__WIN64) || (__WIN32)
    #include <SDL.h>
    #include <SDL_image.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#endif

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