#ifndef __BUTTON_H
#define __BUTTON_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <graphic/graphic.h>

class Button : public Graphic {
private:
    SDL_Texture *buttonTexture;
public:
    Button( std::string name, 
            SDL_Rect position = {0, 0, 0, 0},
            SDL_Vector scaleRate = {1, 1},
            SDL_Vector velocity = {0, 0}, 
            SDL_Texture *texture = NULL
    );

    /**
     * @brief Render the button
     * @return 0 if success
     */
    virtual int render();

    /**
     * @brief Set texture for button
     * @param texture Texture of button
     * @return 0 if success
     */
    int setTexture(SDL_Texture *texture) {
        this->buttonTexture = texture;
        return 0;
    }
};

#endif