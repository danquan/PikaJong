#include <SDL.h>
#include <cstdio>
#include "menu.h"
#include "definition.h"
#include "constant.h"
#include "tiles.h"
#include "game_run.h"

cellStatus cellStartButton;
cellStatus levelText;
extern type_Screen currentScreen;

void menuRender(SDL_Renderer *gRenderer) {
    if(Mix_PlayingMusic() == 0) {
        Mix_PlayMusic( gMusic, -1 );
    }
    else if(Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }

    for(int i = 0; i * TILE_WIDTH < SCREEN_WIDTH; ++i)
        for(int j = 0; j * TILE_HEIGHT < SCREEN_HEIGHT; ++j)
            if((i & 1) == (j & 1)) {
                SDL_Rect tempRect = {i * TILE_WIDTH, j * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
                SDL_RenderCopy(gRenderer, chosen_Highlight, NULL, &tempRect);
            }
    
    //SDL_RenderCopy(gRenderer, levelText.getTexture(), NULL, &levelText.dstRect);
    SDL_RenderCopy(gRenderer, cellStartButton.getTexture(), NULL, &cellStartButton.dstRect);

    SDL_Rect dstRect = {(SCREEN_WIDTH - MAHJONG_WIDTH) / 2, (SCREEN_HEIGHT / 3 * 2 - MAHJONG_HEGHT) / 2 + 50, MAHJONG_WIDTH, MAHJONG_HEGHT};
    //                                                                                                  + 50 to make image down 50 pixel
    SDL_RenderCopy(gRenderer, mahjong_Screen.getTexture(), NULL, &dstRect);
}


void processMenuMouseDown(int x, int y) {
    
    if( Inside(cellStartButton.dstRect, {x, y}) ) {
        currentScreen = GAME_SCREEN;
        return;
    }
}

void createLevelChosen(SDL_Renderer *gRenderer) {
    SDL_Color colorLevelText = {0, 0, 0};
    SDL_Rect dstRect = {0, 0, LEVEL_WIDTH, LEVEL_HEIGHT};
    SDL_Surface *tempLevel = TTF_RenderText_Solid(pixel_like_font, "LEVEL:", colorLevelText);
    SDL_Texture *tempLevelText = SDL_CreateTextureFromSurface(gRenderer, tempLevel);
    textureObject *objectLevelText = new textureObject();

    objectLevelText->assignTexture(tempLevelText, tempLevel->w, tempLevel->h);

    levelText.set(objectLevelText, dstRect);
}

void createStartButton() {
    SDL_Rect dstRect = {(SCREEN_WIDTH - BUTTON_WIDTH) / 2, (SCREEN_HEIGHT / 3 - BUTTON_HEIGHT) / 2 + SCREEN_HEIGHT * 2 / 3, BUTTON_WIDTH, BUTTON_HEIGHT};
    cellStartButton.set(&startButton, dstRect);
}