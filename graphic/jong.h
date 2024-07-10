#ifndef __TILES_H
#define __TILES_H

#if defined(_WIN64) || defined(_WIN32)
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#endif

#include <graphic.h>

class Jong : public Graphic {
private:
    SDL_Texture *jongTile;
public:
    Jong(SDL_Texture *jong, std::string name, SDL_Rect dstRect);
    
    /**
     * @brief Render the Jong
     * @return 0 if success
     */
    virtual int render();
};

#endif