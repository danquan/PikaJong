#ifndef __SCREEN_H
#define __SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <graphic/graphic.h>

class Screen : public Graphic
{
protected:
    SDL_Texture *background;   
public:
    Screen(std::string name,
           SDL_Rect position = {0, 0, 0, 0},
           SDL_Vector scaleRate = {1, 1},
           SDL_Vector velocity = {0, 0},
           SDL_Texture *background = NULL
    );

    /*
     * @brief Render the screen
     * @return 0 if success
     */
    virtual int render();

    /*
     * @brief Set background for screen
     * @param background Texture of background
     * @return 0 if success
     */
    int setBackground(SDL_Texture *background) {
        this->background = background;
        return 0;
    }
};

#endif