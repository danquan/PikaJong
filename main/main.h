#ifndef __MAIN_H
#define __MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

const char* CONFIG_PATH = "data\\config\\config.json";

/*
 * @brief Main game loop
 * @return 0 if success, otherwise return error code
 */
int gameLoop();

/*
 * @brief Init program
 * @return 0 if success, otherwise return error code
 */
int initProgram();

/*
 * @brief Close window, destroy renderer to quit
 */
void closeObject();


#endif
