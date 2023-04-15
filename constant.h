#ifndef __CONSTANT_H
#define __CONSTANT_H
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
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

// Number of model of tile
const int NUM_TILES = 33;// Base on number of tiles in list_tiles.txt
const int MAX_NUM_TEXTURES = NUM_TILES + 14; 
/* 
winScreen, startButton * 2 (mouse out and mouse over), backButton * 2 (mouse out and mouse over), continueButton * 2(...)
Highlight, frontTile, backGround
nextLevel * 2 (mouse over), prevLevel * 2 (mouse over)
*/
const int MAX_MUSICS = 2; // maximum number of musics used

const int LEVEL_WIDTH = 120; // size for text level
const int LEVEL_HEIGHT = 30; // size for text level

const int MAHJONG_WIDTH = 720; // Base on Mahjong.png size
const int MAHJONG_HEGHT = 540; // Base on Mahjong.png size

const int SEGMENT_COUNT_EXIST = 20; // Number of times line is appear when 2 tiles are matched

#ifdef __MAIN_H
    textureObject textures[MAX_NUM_TEXTURES]; // for storing textures
    Mix_Music *musics[MAX_MUSICS];
    Mix_Chunk *chunks[MAX_MUSICS];
#else
    extern textureObject textures[MAX_NUM_TEXTURES];// for storing textures
    extern Mix_Music *musics[MAX_MUSICS];
    extern Mix_Chunk *chunks[MAX_MUSICS];
    extern SDL_Renderer *gRenderer;
#endif

enum type_Tiles {
    RANDOM_TYPE,
    BLACK_TILE,
    REGULAR_TILE
};

enum type_Screen {
    MENU_SCREEN,
    GAME_SCREEN
};

enum name_Music{
    THEME_MUSIC = 0,
    GAME_LOOP_MUSIC = 1
};

enum name_Chunk{
    START_CHUNK = 0,
    WIN_CHUNK = 1
};  

enum name_Texture{
    WIN_SCREEN = NUM_TILES,
    BACK_BUTTON = NUM_TILES + 1,
    BACK_BUTTON_MOUSEOVER = NUM_TILES + 7,
    START_BUTTON = NUM_TILES + 2,
    START_BUTTON_MOUSEOVER = NUM_TILES + 3,
    HIGH_LIGHT = NUM_TILES + 4,
    TILE_FRONT = NUM_TILES + 5,
    BACK_GROUND = NUM_TILES + 6,
    CONTINUE_BUTTON = NUM_TILES + 8,
    CONTINUE_BUTTON_MOUSEOVER = NUM_TILES + 9,
    NEXT_LEVEL = NUM_TILES + 10,
    NEXT_LEVEL_MOUSEOVER = NUM_TILES + 11,
    PREV_LEVEL = NUM_TILES + 12,
    PREV_LEVEL_MOUSEOVER = NUM_TILES + 13
};

#endif