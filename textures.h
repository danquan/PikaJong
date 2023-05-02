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


class LTexture{
private:
    SDL_Texture* texture;
    SDL_Rect dstRect; // Destination Rect, where this cell locate

public:

    LTexture() {
        texture = NULL;
    }

    SDL_Rect* getRect() {return &dstRect;}
    bool empty() {return texture == NULL;}
    SDL_Texture* getTexture() { return texture; }
    
    void Render(SDL_Renderer *gRenderer);
    void set(SDL_Texture* texture, SDL_Rect dstRect);
    void reset();
};

class Pika_Tile : public LTexture {
    public:
    Pika_Tile() {
         reset();
    }
};

class LButton : public LTexture {
    public:
    LButton() {
        reset();
    }
};

class LText : public LTexture {
    public:
    LText () {
        reset();
    }
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