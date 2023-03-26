#ifndef __GAME_RUN_H
#define __GAME_RUN_H

#include <SDL.h>
#include "constant.h"
#include "tiles.h"

void gameRender(SDL_Renderer *Renderer); // Render play screen
void assignLevel(const std::string &lv); // set level for game

void setCell(int x, int y, tilesObject *tile, SDL_Rect dstRect);
void resetCell(int x, int y);

bool canReach(int x, int y, int z, int t); // Do BFS Searching

/*
(x, y) -> position where the mouse click on
*/
void processGameMouseDown(int x, int y); // detect and process when click mouse

#endif