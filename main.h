#ifndef __MAIN_H
#define __MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "tiles.h"
#include "constant.h"

SDL_Window *gWindow= NULL; // Main Window
SDL_Renderer *gRenderer = NULL; // Main gRenderer to Main Window

int currentScreen = GAME_SCREEN; // type_Screen

/*Load tiles, background,...*/
void loadMedia(type_Tiles typeCell = RANDOM_TYPE);

/*Init WINDOW, RENDERER*/
void initProgram();

/*Close window, destroy renderer to quit*/
void closeObject();

#endif
