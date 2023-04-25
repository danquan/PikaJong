#ifndef __MENU_H
#define __MENU_H

#if defined(_WIN64) || defined(_WIN32)
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif


void menuRender();
void processMenuMouseDown(int x, int y);
void processMenuMouseOver(int x, int y);
void createMenu(); // call for all to prepare menu

#endif