#ifndef __DEFINITION_H
#define __DEFINITION_H


#include <iostream>
#if defined(_WIN64) || defined(_WIN32)
    #include <SDL.h>
    #include <SDL_ttf.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
#endif

#ifdef __MAIN_H

bool Inside(const SDL_Rect &mRect, const SDL_Point &mPoint)
{
    return mRect.x <= mPoint.x && mPoint.x < mRect.x + mRect.w &&
           mRect.y <= mPoint.y && mPoint.y < mRect.y + mRect.h;
}
SDL_Point Center(const SDL_Rect &mRect)
{
    return {(mRect.x + (mRect.x + mRect.w - 1)) / 2, (mRect.y + (mRect.y + mRect.h)) / 2};
}
int min(int x, int y)
{
    return x < y ? x : y;
}
std::string int_to_string(int v)
{
    if (v == 0)
        return "0";

    std::string s;

    while (v > 0)
    {
        s.push_back(char(v % 10 + '0'));
        v /= 10;
    }
    for (int i = 0; i * 2 < (int)s.size(); ++i)
        std::swap(s[i], s[s.size() - 1 - i]);

    return s;
}

SDL_Texture *text_to_texture(SDL_Renderer *gRenderer, const std::string &text, const std::string &link_font, int size_font, SDL_Rect &dstRect, SDL_Color colorText) {
    TTF_Font *font = TTF_OpenFont(link_font.c_str(), size_font);
    if (font == NULL)
    {
        std::cout << "No font \"" << link_font << "\" found\n";
        exit(-1);
    }

    SDL_Surface *tempSurface = TTF_RenderText_Solid(font, text.c_str(), colorText);
    if (tempSurface == NULL)
    {
        std::cout << "Can't load surface from text:')";
        exit(-1);
    }

    dstRect.w = tempSurface->w;
    dstRect.h = tempSurface->h;

    SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);
    if (tempSurface == NULL)
    {
        std::cout << "Can't load texture from text :')";
        exit(-1);
    }

    TTF_CloseFont(font);
    SDL_FreeSurface(tempSurface);

    return tempTexture;
}

void Render_Texture(SDL_Renderer *gRenderer, SDL_Texture *tempTexture, SDL_Rect dstRect)
{
    //std::cerr << dstRect.x << " " << dstRect.y << " " << dstRect.w << " " << dstRect.h << "\n";
    SDL_RenderCopy(gRenderer, tempTexture, NULL, &dstRect);
    SDL_DestroyTexture(tempTexture);
}

void SetVolume(int x) {
#if defined(_WIN64) || defined(_WIN32)
    Mix_MasterVolume(x);
#else
    Mix_MasterVolume(x);
#endif
}

void draw_rect_with_alpha(SDL_Renderer* renderer, SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderFillRect(renderer, &rect);
}

#else
extern bool Inside(const SDL_Rect &mRect, const SDL_Point &mPoint);
extern SDL_Point Center(const SDL_Rect &mRect);
extern int min(int x, int y);
extern std::string int_to_string(int v);
extern void Render_Texture(SDL_Renderer *gRenderer, SDL_Texture *tempTexture, SDL_Rect dstRect);
extern void draw_rect_with_alpha(SDL_Renderer* renderer, SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
extern SDL_Texture *text_to_texture(SDL_Renderer *gRenderer, const std::string &text, const std::string &link_font, int size_font, SDL_Rect &dstRect, SDL_Color colorText);
extern void void SetVolume(int x);
#endif

#endif