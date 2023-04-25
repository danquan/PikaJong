#ifndef __MAIN_H
#define __MAIN_H

#if defined(_WIN64) || defined(_WIN32)
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
#endif

#include "textures.h"
#include "constant.h"

SDL_Window *gWindow= NULL; // Main Window
SDL_Renderer *gRenderer = NULL; // Main gRenderer to Main Window

type_Screen currentScreen = MENU_SCREEN; // type_Screen
/*Load chunck*/
void loadChunk(Mix_Chunk *&gChunck, std::string links);

/*Load music*/
void loadMusic(Mix_Music *&gMusic, std::string links);

/*Load Image*/
void loadImage(SDL_Texture* &ImageObject, const std::string &links);

/*Load tiles, background,...*/
void loadMedia(type_Tiles typeCell = RANDOM_TYPE);

/*Init WINDOW, RENDERER*/
void initProgram();

/*Close window, destroy renderer to quit*/
void closeObject();

#endif
