#ifndef __SCREEN_H
#define __SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <graphic.h>

class Screen : public Graphic
{
protected:
    SDL_Texture *background;   
public:
    Screen(SDL_Texture *background, std::string name, SDL_Rect position);

    /*
     * @brief Render the screen
     * @return 0 if success
     */
    virtual int render();
};

#endif