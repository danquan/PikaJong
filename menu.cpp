#include <SDL.h>
#include <cstdio>
#include "menu.h"
#include "definition.h"
#include "constant.h"
#include "tiles.h"

cellStatus cellStartButton;
extern type_Screen currentScreen;

void menuRender(SDL_Renderer *gRenderer) {

    SDL_RenderCopy(gRenderer, cellStartButton.getTexture(), NULL, &cellStartButton.dstRect);
}


void processMenuMouseDown(int x, int y) {

    if( Inside(cellStartButton.dstRect, {x, y}) ) {
        currentScreen = GAME_SCREEN;
        return;
    }
}

void createStartButton() {
    SDL_Rect dstRect = {(SCREEN_WIDTH - BUTTON_WIDTH) / 2, (SCREEN_HEIGHT / 2 - BUTTON_HEIGHT) / 2 + SCREEN_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT};
    cellStartButton.set(&startButton, dstRect);
}