#if defined(_WIN64) || defined(_WIN32)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <cstdio>
#include <fstream>
#include <vector>
#include <cassert>
#include "menu.h"
#include "definition.h"
#include "constant.h"
#include "textures.h"
#include "game_run.h"

SDL_Rect configTable;

enum CONSTANT_TEXT
{
    TEXT_LEVEL,
    CURRENT_LEVEL,
    TEXT_THEME,
    CURRENT_THEME,
    MAX_TEXTS
};
LText Text[MAX_TEXTS];

// Consider BUTTON_MOUSEOVER ^ 1 = BUTTON
enum TEXTURE_FROM_TEXT
{
    TEXTURE_NEXT,
    TEXTURE_NEXT_MOUSEOVER,
    TEXTURE_PREV,
    TEXTURE_PREV_MOUSEOVER,
    MAX_NUM_TEXTURES_FROM_TEXT
};
SDL_Texture *textures_text[MAX_NUM_TEXTURES_FROM_TEXT];

enum MENU_BUTTONS
{
    BUTTON_NEXT_LEVEL,
    BUTTON_PREV_LEVEL,
    BUTTON_NEXT_THEME,
    BUTTON_PREV_THEME,
    BUTTON_CONTINUE,
    BUTTON_START,
    MAX_MENU_BUTTONS
};
LButton menu_Button[MAX_MENU_BUTTONS];

bool canContinue = false; // if player can continue the remaining game

extern type_Screen currentScreen;
extern int currentTheme;

std::vector<std::string> list_levels;
extern std::vector<std::string> list_themes;
int currentLevel = 0;

void menuRender()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(musics[currentTheme][THEME_MUSIC], -1);
    }

    {
        draw_rect_with_alpha(gRenderer, configTable, 0, 0, 0, 128);

        Text[TEXT_LEVEL].Render(gRenderer);
        Text[CURRENT_LEVEL].Render(gRenderer);
        menu_Button[BUTTON_NEXT_LEVEL].Render(gRenderer);
        menu_Button[BUTTON_PREV_LEVEL].Render(gRenderer);
        Text[TEXT_THEME].Render(gRenderer);
        Text[CURRENT_THEME].Render(gRenderer);
        menu_Button[BUTTON_NEXT_THEME].Render(gRenderer);
        menu_Button[BUTTON_PREV_THEME].Render(gRenderer);
    }

    if (canContinue)
        menu_Button[BUTTON_CONTINUE].Render(gRenderer);

    menu_Button[BUTTON_START].Render(gRenderer);
}

// use to change screen set when play another level
void updateLevel()
{
    SDL_Rect dstRect = *Text[CURRENT_LEVEL].getRect();
    SDL_Texture *tempTexture = text_to_texture(gRenderer, list_levels[currentLevel], "fonts\/comic-sans.ttf", 40, dstRect, {255, 255, 255});
    Text[CURRENT_LEVEL].set(tempTexture, {(configTable.w - dstRect.w) / 2 + configTable.x, dstRect.y, dstRect.w, dstRect.h});
    canContinue = false;
}

// use to change screen set when choose another theme
void updateTheme() {
    SDL_Rect dstRect = *Text[CURRENT_THEME].getRect();
    SDL_Texture *tempTexture = text_to_texture(gRenderer, list_themes[currentTheme], "fonts\/comic-sans.ttf", 40, dstRect, {255, 255, 255});
    Text[CURRENT_THEME].set(tempTexture, {(configTable.w - dstRect.w) / 2 + configTable.x, dstRect.y, dstRect.w, dstRect.h});
    canContinue = false;

    if(Mix_PlayingMusic()){
        Mix_HaltMusic();
    }
}

void processMenuMouseDown(int x, int y)
{
    // Start new game
    if (Inside(*menu_Button[BUTTON_START].getRect(), {x, y}))
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

    // Continue playing game
    if (canContinue && Inside(*menu_Button[BUTTON_CONTINUE].getRect(), {x, y}))
    {
        currentScreen = GAME_SCREEN;

        if (Mix_PlayingMusic() != 0)
        {
            Mix_HaltMusic();
        }
        return;
    }

    // mext level
    if (Inside(*menu_Button[BUTTON_NEXT_LEVEL].getRect(), {x, y}))
    {
        currentLevel = currentLevel == (int)list_levels.size() - 1 ? 0 : currentLevel + 1;
        updateLevel(); // update screen
    }

    // previous level
    if (Inside(*menu_Button[BUTTON_PREV_LEVEL].getRect(), {x, y}))
    {
        currentLevel = currentLevel == 0 ? (int)list_levels.size() - 1 : currentLevel - 1;
        updateLevel(); // update screen
    }

    // next theme
    if (Inside(*menu_Button[BUTTON_NEXT_THEME].getRect(), {x, y}))
    {
        currentTheme = currentTheme == (int)list_themes.size() - 1 ? 0 : currentTheme + 1;
        updateTheme(); // update screen
    }

    // previous theme
    if (Inside(*menu_Button[BUTTON_PREV_THEME].getRect(), {x, y}))
    {
        currentTheme = currentTheme == 0 ? (int)list_themes.size() - 1 : currentTheme - 1;
        updateTheme(); // update screen
    }
}

void processMenuMouseOver(int x, int y)
{
    if (Inside(*menu_Button[BUTTON_START].getRect(), {x, y}))
    {
        menu_Button[BUTTON_START].set(textures[currentTheme][TEXTURE_START_BUTTON_MOUSEOVER], *menu_Button[BUTTON_START].getRect());
    }
    else
    {
        menu_Button[BUTTON_START].set(textures[currentTheme][TEXTURE_START_BUTTON], *menu_Button[BUTTON_START].getRect());
    }

    if (canContinue == true)
    {
        if (Inside(*menu_Button[BUTTON_CONTINUE].getRect(), {x, y}))
        {
            menu_Button[BUTTON_CONTINUE].set(textures[currentTheme][TEXTURE_CONTINUE_BUTTON_MOUSEOVER], *menu_Button[BUTTON_CONTINUE].getRect());
        }
        else
        {
            menu_Button[BUTTON_CONTINUE].set(textures[currentTheme][TEXTURE_CONTINUE_BUTTON], *menu_Button[BUTTON_CONTINUE].getRect());
        }
    }

    for(int button_id : {BUTTON_NEXT_LEVEL,
                         BUTTON_NEXT_THEME}) 
    {
        if(Inside(*menu_Button[button_id].getRect(), {x, y}))
            menu_Button[button_id].set(textures_text[TEXTURE_NEXT_MOUSEOVER], *menu_Button[button_id].getRect());
        else 
            menu_Button[button_id].set(textures_text[TEXTURE_NEXT], *menu_Button[button_id].getRect());
    }

    for(int button_id : {BUTTON_PREV_LEVEL,
                         BUTTON_PREV_THEME}) 
    {
        if(Inside(*menu_Button[button_id].getRect(), {x, y}))
            menu_Button[button_id].set(textures_text[TEXTURE_PREV_MOUSEOVER], *menu_Button[button_id].getRect());
        else 
            menu_Button[button_id].set(textures_text[TEXTURE_PREV], *menu_Button[button_id].getRect());
    }
}

void createConfigTable()
{
    // back groung of config table
    configTable = {(SCREEN_WIDTH - 780) / 2, (menu_Button[BUTTON_START].getRect()->y - 460) / 2, 780, 460};

    SDL_Rect dstRect = {0, configTable.y + 50, 0, 0};

    /*Render Level chosen*/
    {
        /*
                 LEVEL
            < `currentLevel` >
        */

        // First, render text
        SDL_Texture *tempTexture = text_to_texture(gRenderer, "LEVEL", "fonts\/comic-sans-bold.ttf", 40, dstRect, {255, 255, 255});
        Text[TEXT_LEVEL].set(tempTexture, {(configTable.w - dstRect.w) / 2 + configTable.x, dstRect.y, dstRect.w, dstRect.h});

        // then, render level
        dstRect.y += dstRect.h + 20;
        tempTexture = text_to_texture(gRenderer, list_levels[currentLevel], "fonts\/comic-sans.ttf", 40, dstRect, {255, 255, 255});
        Text[CURRENT_LEVEL].set(tempTexture, {(configTable.w - dstRect.w) / 2 + configTable.x, dstRect.y, dstRect.w, dstRect.h});

        textures_text[TEXTURE_NEXT] = text_to_texture(gRenderer, ">", "fonts\/comic-sans-bold.ttf", 40, dstRect, {255, 255, 255});
        textures_text[TEXTURE_NEXT_MOUSEOVER] = text_to_texture(gRenderer, ">", "fonts\/comic-sans-bold.ttf", 40, dstRect, {255, 0, 0});
        menu_Button[BUTTON_NEXT_LEVEL].set(textures_text[TEXTURE_NEXT], {configTable.w * 3 / 4 + configTable.x, dstRect.y, dstRect.w, dstRect.h});

        textures_text[TEXTURE_PREV] = text_to_texture(gRenderer, "<", "fonts\/comic-sans-bold.ttf", 40, dstRect, {255, 255, 255});
        textures_text[TEXTURE_PREV_MOUSEOVER] = text_to_texture(gRenderer, "<", "fonts\/comic-sans-bold.ttf", 40, dstRect, {255, 0, 0});
        menu_Button[BUTTON_PREV_LEVEL].set(textures_text[TEXTURE_PREV], {configTable.w / 4 + configTable.x, dstRect.y, dstRect.w, dstRect.h});
    }

    dstRect.y += dstRect.h + 50;

    /*Render Theme chosen*/
    {
        /*
                 THEME
            < `currentTheme` >
        */

        // First, render text
        SDL_Texture *tempTexture = text_to_texture(gRenderer, "THEME", "fonts\/comic-sans-bold.ttf", 40, dstRect, {255, 255, 255});
        Text[TEXT_THEME].set(tempTexture, {(configTable.w - dstRect.w) / 2 + configTable.x, dstRect.y, dstRect.w, dstRect.h});

        // then, render level
        dstRect.y += dstRect.h + 20;
        tempTexture = text_to_texture(gRenderer, list_themes[currentTheme], "fonts\/comic-sans.ttf", 40, dstRect, {255, 255, 255});
        Text[CURRENT_THEME].set(tempTexture, {(configTable.w - dstRect.w) / 2 + configTable.x, dstRect.y, dstRect.w, dstRect.h});

        dstRect.w = menu_Button[BUTTON_NEXT_LEVEL].getRect()->w;
        dstRect.h = menu_Button[BUTTON_NEXT_LEVEL].getRect()->h;
        menu_Button[BUTTON_NEXT_THEME].set(textures_text[TEXTURE_NEXT], {configTable.w * 3 / 4 + configTable.x, dstRect.y, dstRect.w, dstRect.h});

        dstRect.w = menu_Button[BUTTON_PREV_LEVEL].getRect()->w;
        dstRect.h = menu_Button[BUTTON_PREV_LEVEL].getRect()->h;
        menu_Button[BUTTON_PREV_THEME].set(textures_text[TEXTURE_PREV], {configTable.w / 4 + configTable.x, dstRect.y, dstRect.w, dstRect.h});
    }
}

void createStartButton()
{
    SDL_Rect dstRect = {(SCREEN_WIDTH - 167) / 2, (SCREEN_HEIGHT / 3 - 68) / 2 + SCREEN_HEIGHT * 2 / 3, 167, 68};
    menu_Button[BUTTON_START].set(textures[currentTheme][TEXTURE_START_BUTTON], dstRect);
}

void createContinueButton()
{
    // continue button lie up to the start
    SDL_Rect dstRect = {menu_Button[BUTTON_START].getRect()->x, menu_Button[BUTTON_START].getRect()->y - 68, 167, 68};
    menu_Button[BUTTON_CONTINUE].set(textures[currentTheme][TEXTURE_CONTINUE_BUTTON], dstRect);
}

// read list of levels
void readLevels()
{
    std::ifstream in("levels\/list-levels.txt");
    std::string name_level;

    while (in >> name_level)
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
