#ifndef __GAME_RUN_H
#define __GAME_RUN_H

#include "textures.h"

void gameRender(SDL_Renderer *Renderer); // Render play screen
void assignLevel(const std::string &lv); // set level for game
void createBackButton(); // use for back button
void createWinScreen();

void setCell(cellStatus &cell, textureObject tile, SDL_Rect dstRect);

void doSearch(SDL_Point src, SDL_Point dst); // Do BFS Searching
void Trace(SDL_Point src, SDL_Point dst, int dir, int numchange); // For making segments

/*
(x, y) -> position where the mouse click on
*/
void processGameMouseDown(int x, int y); // detect and process when click mouse

#endif