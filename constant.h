#ifndef __CONSTANT_H
#define __CONSTANT_H
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include "tiles.h"

// Screen size
const int SCREEN_WIDTH = 1260;
const int SCREEN_HEIGHT = 780;

// Tiles size
const int TILE_WIDTH = 45;
const int TILE_HEIGHT = 60;
const int CELL_WIDTH = 45 + 1; // We add 1 for a pixel between 2 tiles
const int CELL_HEIGHT = 60 + 1; // We add 1 for a pixel between 2 tiles

// Table Size. This can change by add more level
const int MAX_ROWS = 11;
const int MAX_COLUMNS = 20;

// Number of model of tile
const int MAX_NUM_TILES = 33; // Base on number of tiles in list_tiles.txt

const int BUTTON_WIDTH = 167; // Base on Button START Size
const int BUTTON_HEIGHT = 68; // Base on Button START Size

const int LEVEL_WIDTH = 120;
const int LEVEL_HEIGHT = 30;

const int MAHJONG_WIDTH = 720; // Base on Mahjong size
const int MAHJONG_HEGHT = 540; // Base on Mahjong size


#ifdef __MAIN_H
    textureObject tile[MAX_NUM_TILES]; // for storing tiles
    SDL_Texture *chosen_Highlight = NULL; // use to highlight chosen cells
    textureObject win_Screen; // use to show when player win game
    textureObject mahjong_Screen; // use to show on menu
    textureObject startButton; // use for start game click
    textureObject backButton; // use for back to menu screen
    TTF_Font *pixel_like_font = NULL;
    Mix_Music *gMusic = NULL;
    Mix_Chunk *winMusic = NULL;
#else
    extern textureObject tile[MAX_NUM_TILES]; // for storing tiles
    extern SDL_Texture *chosen_Highlight; // use to highlight chosen cells
    extern textureObject win_Screen; // use to show when player win game
    extern textureObject mahjong_Screen; // use to show on menu
    extern textureObject startButton; // use for start game click
    extern textureObject backButton; // use for back to menu screen
    extern TTF_Font *pixel_like_font;
    extern Mix_Music *gMusic;
    extern Mix_Chunk *winMusic;
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

#endif