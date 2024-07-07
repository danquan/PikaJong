#ifndef __CONSTANT_H
#define __CONSTANT_H

#if defined(_WIN64) || defined(_WIN32)
    #include <SDL.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
#endif

#include <string>
#include "textures.h"

// Screen size
const int SCREEN_WIDTH = 1260;
const int SCREEN_HEIGHT = 780;

// Tiles size
const int TILE_WIDTH = 45;
const int TILE_HEIGHT = 60;
const int CELL_WIDTH = 45 + 3; // We add 1 for a pixel between 2 tiles
const int CELL_HEIGHT = 60 + 3; // We add 1 for a pixel between 2 tiles

// Table Size. This can change by add more level
const int MAX_ROWS = 11;
const int MAX_COLUMNS = 20;

const int MAX_NUM_TILES = 33; // base on the number of lines in file list_tiles.txt
const int MAX_NUM_THEMES = 2; // base on the number of lines in file list_themes.txt

const int SEGMENT_COUNT_EXIST = 17; // Number of times line is appear when 2 tiles are matched

enum type_Screen {
    MENU_SCREEN,
    GAME_SCREEN,
    WIN_SCREEN
};

enum name_Music{
    THEME_MUSIC,
    GAME_LOOP_MUSIC,
    MAX_MUSICS
};

enum name_Chunk{
    START_CHUNK,
    WIN_CHUNK,
    MAX_CHUNKS
};  

// Consider BUTTON_MOUSEOVER ^ 1 = BUTTON
enum name_Texture{
    TEXTURE_BACK_BUTTON,
    TEXTURE_BACK_BUTTON_MOUSEOVER,
    TEXTURE_START_BUTTON,
    TEXTURE_START_BUTTON_MOUSEOVER,
    TEXTURE_CONTINUE_BUTTON,
    TEXTURE_CONTINUE_BUTTON_MOUSEOVER,
    TEXTURE_BACK_GROUND,
    TEXTURE_SCRREEN_WIN,
    TEXTURE_HIGH_LIGHT,
    MAX_NUM_TEXTURES
};

#ifdef __MAIN_H
    SDL_Texture* textures[MAX_NUM_THEMES][MAX_NUM_TEXTURES]; // for storing textures
    SDL_Texture* tiles[MAX_NUM_THEMES][MAX_NUM_TILES];
    Mix_Music *musics[MAX_NUM_THEMES][MAX_MUSICS];
    Mix_Chunk *chunks[MAX_NUM_THEMES][MAX_CHUNKS];
#else
    extern SDL_Texture* textures[MAX_NUM_THEMES][MAX_NUM_TEXTURES];// for storing textures
    extern SDL_Texture* tiles[MAX_NUM_THEMES][MAX_NUM_TILES];
    extern Mix_Music *musics[MAX_NUM_THEMES][MAX_MUSICS];
    extern Mix_Chunk *chunks[MAX_NUM_THEMES][MAX_CHUNKS];
    extern SDL_Renderer *gRenderer;
#endif


#endif