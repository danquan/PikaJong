#ifndef __MENU_H
#define __MENU_H

#include <SDL.h>

void menuRender();
void processMenuMouseDown(int x, int y);
void processMenuMouseOver(int x, int y);
void createMenu(); // call for all to prepare menu

#endif