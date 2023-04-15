#include <SDL.h>
#include <cstdio>
#include <fstream>
#include <cassert>
#include "menu.h"
#include "definition.h"
#include "constant.h"
#include "textures.h"
#include "game_run.h"

cellStatus cellStartButton, cellContinueButton;
SDL_Rect configTable;
cellStatus level_text;
cellStatus chosen_level, next_Level, prev_Level;

bool canContinue = false; // if player can continue the remaining game

extern type_Screen currentScreen;
std::vector<std::string> list_levels;
int currentLevel = 0;


void menuRender()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(musics[THEME_MUSIC], -1);
    }

    draw_rect_with_alpha(gRenderer, configTable, 0, 0, 0, 128);
    
    level_text.Render(gRenderer);
    chosen_level.Render(gRenderer);
    next_Level.Render(gRenderer);
    prev_Level.Render(gRenderer);

    if(canContinue)
        cellContinueButton.Render(gRenderer);

    cellStartButton.Render(gRenderer);
}

void processMenuMouseDown(int x, int y)
{

    if (Inside(*cellStartButton.getRect(), {x, y}))
    {
        currentScreen = GAME_SCREEN;

        if (Mix_PlayingMusic() != 0)
        {
            Mix_HaltMusic();
        }
        assert(currentLevel < (int)list_levels.size());
        assignLevel(list_levels[currentLevel]);
        return;
    }

    if (canContinue && Inside(*cellContinueButton.getRect(), {x, y}))
    {
        currentScreen = GAME_SCREEN;

        if (Mix_PlayingMusic() != 0)
        {
            Mix_HaltMusic();
        }
        return;
    }

    if(Inside(*next_Level.getRect(), {x, y})) {
        currentLevel = currentLevel == (int)list_levels.size() - 1 ? 0 : currentLevel + 1;
        SDL_Rect dstRect = *chosen_level.getRect();
        SDL_Texture *tempTexture = text_to_texture(gRenderer, list_levels[currentLevel], "fonts\\comic-sans.ttf", 40, dstRect, {255, 255, 255});
        chosen_level.set(tempTexture, {(configTable.w - dstRect.w) / 2 + configTable.x, dstRect.y, dstRect.w, dstRect.h});
        canContinue = false;
    }

    if(Inside(*prev_Level.getRect(), {x, y})) {
        currentLevel = currentLevel == 0 ? (int)list_levels.size() - 1 : currentLevel - 1;
        SDL_Rect dstRect = *chosen_level.getRect();
        SDL_Texture *tempTexture = text_to_texture(gRenderer, list_levels[currentLevel], "fonts\\comic-sans.ttf", 40, dstRect, {255, 255, 255});
        chosen_level.set(tempTexture, {(configTable.w - dstRect.w) / 2 + configTable.x, dstRect.y, dstRect.w, dstRect.h});
        canContinue = false;
    }
}

void processMenuMouseOver(int x, int y)
{
    if (Inside(*cellStartButton.getRect(), {x, y}))
    {
        cellStartButton.set(textures[START_BUTTON_MOUSEOVER], *cellStartButton.getRect());
    }
    else
    {
        cellStartButton.set(textures[START_BUTTON], *cellStartButton.getRect());
    }

    if (canContinue == true)
    {
        if (Inside(*cellContinueButton.getRect(), {x, y}))
        {
            cellContinueButton.set(textures[CONTINUE_BUTTON_MOUSEOVER], *cellContinueButton.getRect());
        }
        else
        {
            cellContinueButton.set(textures[CONTINUE_BUTTON], *cellContinueButton.getRect());
        }
    }

    if(Inside(*next_Level.getRect(), {x, y})) {
        next_Level.set(textures[NEXT_LEVEL_MOUSEOVER], *next_Level.getRect());
    }
    else {
        next_Level.set(textures[NEXT_LEVEL], *next_Level.getRect());
    }

    if(Inside(*prev_Level.getRect(), {x, y})) {
        prev_Level.set(textures[PREV_LEVEL_MOUSEOVER], *prev_Level.getRect());
    }
    else {
        prev_Level.set(textures[PREV_LEVEL], *prev_Level.getRect());
    }
}

void createConfigTable()
{
    configTable = {(SCREEN_WIDTH - 780) / 2, (cellStartButton.getRect()->y - 460) / 2, 780, 460};

    // First, render text
    SDL_Rect dstRect= {0, configTable.y + 50, 0, 0};
    SDL_Texture *tempTexture = text_to_texture(gRenderer, "LEVEL", "fonts\\comic-sans-bold.ttf", 40, dstRect, {255, 255, 255});
    level_text.set(tempTexture, {(configTable.w - dstRect.w) / 2 + configTable.x, dstRect.y, dstRect.w, dstRect.h});
    
    //then, render level
    dstRect.y += dstRect.h + 20;    
    tempTexture = text_to_texture(gRenderer, list_levels[currentLevel], "fonts\\comic-sans.ttf", 40, dstRect, {255, 255, 255});
    chosen_level.set(tempTexture, {(configTable.w - dstRect.w) / 2 + configTable.x, dstRect.y, dstRect.w, dstRect.h});
    
    textures[NEXT_LEVEL] = text_to_texture(gRenderer, ">", "fonts\\comic-sans-bold.ttf", 40, dstRect, {255, 255, 255});
    textures[NEXT_LEVEL_MOUSEOVER] = text_to_texture(gRenderer, ">", "fonts\\comic-sans-bold.ttf", 40, dstRect, {255, 0, 0});
    next_Level.set(textures[NEXT_LEVEL], {configTable.w * 3 / 4 + configTable.x, dstRect.y, dstRect.w, dstRect.h});
    
    textures[PREV_LEVEL] = text_to_texture(gRenderer, "<", "fonts\\comic-sans-bold.ttf", 40, dstRect, {255, 255, 255});
    textures[PREV_LEVEL_MOUSEOVER] = text_to_texture(gRenderer, "<", "fonts\\comic-sans-bold.ttf", 40, dstRect, {255, 0, 0});
    prev_Level.set(textures[PREV_LEVEL_MOUSEOVER], {configTable.w / 4 + configTable.x, dstRect.y, dstRect.w, dstRect.h});

}

void createStartButton()
{
    SDL_Rect dstRect = {(SCREEN_WIDTH - 167) / 2, (SCREEN_HEIGHT / 3 - 68) / 2 + SCREEN_HEIGHT * 2 / 3, 167, 68};
    cellStartButton.set(textures[START_BUTTON], dstRect);
}

void createContinueButton() {
    // continue button lie up to the start
    SDL_Rect dstRect = {cellStartButton.getRect()->x, cellStartButton.getRect()->y - 68, 167, 68};
    cellContinueButton.set(textures[CONTINUE_BUTTON], dstRect);
}

// read list of levels
void readLevels() {
    std::ifstream in("levels\\list-levels.txt");
    std::string name_level;

    while(in >> name_level)
        list_levels.emplace_back(name_level);
    
    in.close();
}

void createMenu()
{
    readLevels();
    createStartButton();
    createContinueButton();
    createConfigTable();
}