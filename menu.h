#ifndef __MENU_H
#define __MENU_H

#include <SDL.h>

void menuRender(SDL_Renderer *gRenderer);
void processMenuMouseDown(int x, int y);
void createStartButton();
void createLevelChosen(SDL_Renderer *gRenderer);

#endif