#include "tiles.h"
#include "constant.h"

/*Code for tilesObject*/

void tilesObject::free_memory()
{
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    w = h = 0;
}

void tilesObject::assignTexture(SDL_Texture *textTure, int w, int h)
{
    this->mTexture = textTure;
    this->w = w;
    this->h = h;
}

/*Code for cellStatus*/

void cellStatus::reset() {
    this->tile = NULL;
    this->isChosen = false;
    this->isAppear = false;
}

bool cellStatus::click() {
    isChosen = !isChosen;
    if(isChosen)
        return true;
    else 
        return false;
}


void cellStatus::set(tilesObject *tile, SDL_Rect dstRect) {
    this->tile = tile;
    this->dstRect = dstRect;
    this->isChosen = false;
    this->isAppear = true;
}


void cellStatus::disAppear() {
    isAppear = false;
}