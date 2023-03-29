#include "tiles.h"
#include "definition.h"
#include "constant.h"

/*Code for textureObject*/

void textureObject::free_memory()
{
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    w = h = 0;
}

void textureObject::assignTexture(SDL_Texture *textTure, int w, int h)
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


void cellStatus::set(textureObject *tile, SDL_Rect dstRect) {
    this->tile = tile;
    this->dstRect = dstRect;
    this->isChosen = false;
    this->isAppear = true;
}


void cellStatus::disAppear() {
    isAppear = false;
}

/*Segment*/
int traceSegment::Exist() {
    return --numCanExist;
}

void traceSegment::Draw(SDL_Renderer *gRenderer) {
    if(ePoint1.x == ePoint2.x) { // Vertical line
        SDL_Rect tempLine = {ePoint1.x - 1, min(ePoint1.y, ePoint2.y), 3, abs(ePoint1.y - ePoint2.y)};
        SDL_RenderFillRect( gRenderer, &tempLine );
    }
    else { // Horizontal
        SDL_Rect tempLine = {min(ePoint1.x, ePoint2.x), ePoint1.y - 1, abs(ePoint1.x - ePoint2.x), 3};
        SDL_RenderFillRect( gRenderer, &tempLine );
    }
}