#include "textures.h"
#include "definition.h"
#include "constant.h"

/*Code for SDL_Texture**/

/*Code for LTexture*/

void LTexture::Render(SDL_Renderer *gRenderer) {
    if(!empty())
        SDL_RenderCopy(gRenderer, texture, NULL, &dstRect);
}

void LTexture::reset() {
    this->texture = NULL;
}


void LTexture::set(SDL_Texture* texture, SDL_Rect dstRect) {
    this->texture = texture;
    this->dstRect = dstRect;
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