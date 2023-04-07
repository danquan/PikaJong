#include <SDL.h>
#include <cstdio>
#include "menu.h"
#include "definition.h"
#include "constant.h"
#include "textures.h"
#include "game_run.h"

cellStatus cellStartButton,
           cellMahjong;
cellStatus levelText;
extern type_Screen currentScreen;
extern std::string currentLevel;

void menuRender(SDL_Renderer *gRenderer) {
    if(Mix_PlayingMusic() == 0) {
        Mix_PlayMusic( gMusic, -1 );
    }
    else if(Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }

    for(int i = 0; i * TILE_WIDTH < SCREEN_WIDTH; ++i)
        for(int j = 0; j * TILE_HEIGHT < SCREEN_HEIGHT; ++j)
            if((i & 1) == (j & 1)) 
            {
                SDL_Rect tempRect = {i * TILE_WIDTH, j * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
                SDL_RenderCopy(gRenderer, textures[HIGH_LIGHT], NULL, &tempRect);
            }

    cellStartButton.Render(gRenderer);
    cellMahjong.Render(gRenderer);
}


void processMenuMouseDown(int x, int y) {
    
    if( Inside(cellStartButton.dstRect, {x, y}) ) {
        currentScreen = GAME_SCREEN;

        if(Mix_PlayingMusic() != 0) 
        {
            Mix_HaltMusic();
        }

        assignLevel(currentLevel);
        return;
    }
}

void createMahjongScreen() 
{
    SDL_Rect dstRect = {(SCREEN_WIDTH - MAHJONG_WIDTH) / 2, (SCREEN_HEIGHT / 3 * 2 - MAHJONG_HEGHT) / 2 + 50, MAHJONG_WIDTH, MAHJONG_HEGHT};
    cellMahjong.set(textures[MAHJONG_MENU], dstRect);
}

void createStartButton() 
{
    SDL_Rect dstRect = {(SCREEN_WIDTH - BUTTON_WIDTH) / 2, (SCREEN_HEIGHT / 3 - BUTTON_HEIGHT) / 2 + SCREEN_HEIGHT * 2 / 3, BUTTON_WIDTH, BUTTON_HEIGHT};
    cellStartButton.set(textures[START_BUTTON], dstRect);
}