#ifndef __CONSTANT_H
#define __CONSTANT_H
#include <string>
#include <SDL.h>
#include "tiles.h"

// Screen size
const int SCREEN_WIDTH = 1280;
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
const int MAX_NUM_TILES = 22; // Base on number of tiles in list_tiles.txt

const int BUTTON_WIDTH = 167; // Base on Button Size
const int BUTTON_HEIGHT = 68; // Base on Button Size


#ifdef __MAIN_H
    textureObject tile[MAX_NUM_TILES]; // for storing tiles
    SDL_Texture *chosen_Highlight = NULL; // use to highlight chosen cells
    textureObject win_Screen; // use to show when player win game
    textureObject startButton; // use for start game click
#else
    extern textureObject tile[MAX_NUM_TILES]; // for storing tiles
    extern SDL_Texture *chosen_Highlight; // use to highlight chosen cells
    extern textureObject win_Screen; // use to show when player win game
    extern textureObject startButton; // use for start game click
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