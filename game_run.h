#ifndef __GAME_RUN_H
#define __GAME_RUN_H

#include "textures.h"

void gameRender(); // Render play screen
    void render_infoTable(); // render info table
    void render_MahJongTile(cellStatus &cell); // render a tile on table
void assignLevel(const std::string &lv); // set level for game
void createBackButton(); // use for back button
void createWinScreen(); // create win screen
void createGameScreen(); // call to all prepare for game screen, include back button and win screen

void doSearch(SDL_Point src, SDL_Point dst); // Do BFS Searching
void Trace(SDL_Point src, SDL_Point dst, int dir, int numchange); // For making segments

/*
(x, y) -> position where the mouse click on
*/
void processGameMouseDown(int x, int y); // detect and process when click mouse
    void tryConnectChosenTiles();
void processGameMouseOver(int x, int y); // detect mouse over

#endif