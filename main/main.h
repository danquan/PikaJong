#ifndef __MAIN_H
#define __MAIN_H

#if defined(_WIN64) || defined(_WIN32)
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
#endif

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
