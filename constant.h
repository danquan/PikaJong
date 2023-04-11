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
const int MAX_NUM_TEXTURES = NUM_TILES + 6; 
// winScreen, menu_MahjongScreen, startButton, backButton, Highlight, frontTile

const int BUTTON_WIDTH = 167; // Base on Button START Size
const int BUTTON_HEIGHT = 68; // Base on Button START Size

const int LEVEL_WIDTH = 120; // size for text level
const int LEVEL_HEIGHT = 30; // size for text level

const int MAHJONG_WIDTH = 720; // Base on Mahjong.png size
const int MAHJONG_HEGHT = 540; // Base on Mahjong.png size

const int SEGMENT_COUNT_EXIST = 20; // Number of times line is appear when 2 tiles are matched

#ifdef __MAIN_H
    textureObject textures[MAX_NUM_TEXTURES]; // for storing textures
    Mix_Music *gMusic = NULL;
    Mix_Music *gTheme = NULL;
    Mix_Chunk *winMusic = NULL;
    Mix_Chunk *introMusic = NULL;
#else
    extern textureObject textures[MAX_NUM_TEXTURES];// for storing textures
    extern Mix_Music *gMusic;
    extern Mix_Music *gTheme;
    extern Mix_Chunk *winMusic;
    extern Mix_Chunk *introMusic;
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

enum name_Texture{
    WIN_SCREEN = NUM_TILES,
    BACK_BUTTON = NUM_TILES + 1,
    START_BUTTON = NUM_TILES + 2,
    MAHJONG_MENU = NUM_TILES + 3,
    HIGH_LIGHT = NUM_TILES + 4,
    TILE_FRONT = NUM_TILES + 5
};

#endif