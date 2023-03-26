#ifndef __TILES_H
#define __TILES_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

struct tilesObject {
    SDL_Texture *mTexture;
    int w, h;

    tilesObject(SDL_Texture *mTexture = NULL, int w = 0, int h = 0): mTexture(mTexture), w(w), h(h) {}
    ~tilesObject() {
        free_memory();
    }

    int getWidth() {return w;}
    int getHeight() {return h;}
    SDL_Texture *getTexture() {return mTexture;}

    void free_memory();
    void assignTexture(SDL_Texture *textTure, int w, int h);
};

struct cellStatus{
    tilesObject *tile;
    SDL_Rect dstRect; // Destination Rect, where this cell locate
    bool isChosen, isAppear;

    cellStatus() {
        tile = NULL;
        isChosen = false;
        isAppear = false;
    }

    bool empty() {return tile == NULL || !isAppear;}
    bool canClick() {return isAppear;}
    bool getCheckChosen() {return isChosen;}
    SDL_Texture *getTexture() { return tile->getTexture(); }
    
    void set(tilesObject *tile, SDL_Rect dstRect);
    void reset();
    bool click();
    void disAppear();
};

#endif