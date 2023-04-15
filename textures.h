#ifndef __TILES_H
#define __TILES_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using textureObject = SDL_Texture*;

class cellStatus{
private:
    textureObject texture;
    SDL_Rect dstRect; // Destination Rect, where this cell locate

public:

    cellStatus() {
        texture = NULL;
    }

    SDL_Rect* getRect() {return &dstRect;}
    bool empty() {return texture == NULL;}
    textureObject getTexture() { return texture; }
    
    void Render(SDL_Renderer *gRenderer);
    void set(textureObject texture, SDL_Rect dstRect);
    void reset();
};

class traceSegment {
private:
    SDL_Point ePoint1, ePoint2; // location of 2 end-points
    int numCanExist;
public:
    traceSegment(const SDL_Point &ePoint1, const SDL_Point &ePoint2, const int &numCanExist): 
        ePoint1(ePoint1), ePoint2(ePoint2), numCanExist(numCanExist) {}; 
    
    // If this segment is Existed
    int Exist();
    void Draw(SDL_Renderer *gRenderer);
};

#endif