
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

#include <stdio.h>
#include <string>
#include <fstream>
#include "main.h"
#include "constant.h"
#include "definition.h"
#include "game_run.h"
#include "menu.h"

/// @brief run main process
void run()
{
    createMenu();
    createGameScreen();

    SetVolume(100);

    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (currentScreen == GAME_SCREEN || currentScreen == WIN_SCREEN)
                    processGameMouseDown(x, y);
                else
                    processMenuMouseDown(x, y);
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (currentScreen == MENU_SCREEN)
                    processMenuMouseOver(x, y);
                else
                    processGameMouseOver(x, y);
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 255, 178, 102, 255);
        SDL_RenderClear(gRenderer);
        SDL_Rect tempBackGround = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(gRenderer, textures[currentTheme][TEXTURE_BACK_GROUND], NULL, &tempBackGround);

        // Do something here
        if (currentScreen == MENU_SCREEN)
            menuRender();
        else if (currentScreen == GAME_SCREEN || currentScreen == WIN_SCREEN)
            gameRender();

        // Force Render
        SDL_RenderPresent(gRenderer);
    }
}

int main(int argc, char *argv[])
{
    initProgram();
    read_Themes(); // it's neccessary to be called before loadMedia()
    loadMedia();
    run();
    closeObject();
}

void read_Themes()
{
    std::ifstream inf("list_themes.txt");
    std::string theme;

    while (inf >> theme)
    {
        list_themes.emplace_back(theme);
    }

    inf.close();
}

/// @brief For loading Images from file to texture
/// @param ImageObject texture to save image
/// @param links where image locate
/// @param alpha if alpha mode is enabled, alpha is the alphamod; otherwise, alpha = -1
void loadImage(SDL_Texture *&ImageObject, const std::string &links, int alpha = -1)
{
    /*load Button*/
    SDL_Surface *tempImage = IMG_Load(links.c_str());
    if (tempImage == NULL)
    {
        printf("Fail to load image %s,\n Error: %s\n", links.c_str(), SDL_GetError());
        exit(-1);
    }

    ImageObject = SDL_CreateTextureFromSurface(gRenderer, tempImage);
    if (ImageObject == NULL)
    {
        printf("Fail to create texture from image %s,\n Error: %s\n", links.c_str(), SDL_GetError());
        exit(-1);
    }

    // Set alpha mod
    if (alpha != -1)
    {
        SDL_SetTextureBlendMode(ImageObject, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(ImageObject, alpha);
    }

    SDL_FreeSurface(tempImage);
    tempImage = NULL;
}

void loadChunk(Mix_Chunk *&gChunck, std::string links)
{
    gChunck = Mix_LoadWAV(links.c_str());
    if (gChunck == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(-1);
    }
}

void loadMusic(Mix_Music *&gMusic, std::string links)
{
    gMusic = Mix_LoadMUS(links.c_str());
    if (gMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(-1);
    }
}

void loadMedia()
{
    for (int theme_id = 0; theme_id < (int)list_themes.size(); ++theme_id)
    {
        std::string theme = list_themes[theme_id];

        /*Load Button*/
        loadImage(textures[theme_id][TEXTURE_START_BUTTON], ".\/images\/" + theme + "\/buttons\/start_Button.png", -1);
        loadImage(textures[theme_id][TEXTURE_START_BUTTON_MOUSEOVER], ".\/images\/" + theme + "\/buttons\/start_Button_Mouseover.png", -1);
        loadImage(textures[theme_id][TEXTURE_BACK_BUTTON], ".\/images\/" + theme + "\/buttons\/back_Button.png", -1);
        loadImage(textures[theme_id][TEXTURE_BACK_BUTTON_MOUSEOVER], ".\/images\/" + theme + "\/buttons\/back_Button_Mouseover.png", -1);
        loadImage(textures[theme_id][TEXTURE_CONTINUE_BUTTON], ".\/images\/" + theme + "\/buttons\/continue_Button.png", -1);
        loadImage(textures[theme_id][TEXTURE_CONTINUE_BUTTON_MOUSEOVER], ".\/images\/" + theme + "\/buttons\/continue_Button_Mouseover.png", -1);

        /*load win Screen*/
        loadImage(textures[theme_id][TEXTURE_SCRREEN_WIN], ".\/images\/" + theme + "\/backgrounds\/win.png", -1);

        /*Load Background*/
        loadImage(textures[theme_id][TEXTURE_BACK_GROUND], ".\/images\/" + theme + "\/backgrounds\/background.png", -1);

        /*load music*/
        loadMusic(musics[theme_id][GAME_LOOP_MUSIC], ".\/musics\/" + theme + "\/game_loop.mp3");
        loadMusic(musics[theme_id][THEME_MUSIC], ".\/musics\/" + theme + "\/theme_song.mp3");
        loadChunk(chunks[theme_id][START_CHUNK], ".\/musics\/" + theme + "\/start_game.mp3");
        loadChunk(chunks[theme_id][WIN_CHUNK], ".\/musics\/" + theme + "\/win.mp3");

        std::string links = ".\/images\/" + theme + "\/tiles\/";

        /*load highlight*/
        loadImage(textures[theme_id][TEXTURE_HIGH_LIGHT], links + "Chosen.png", 125);

        /* load all image */
        std::ifstream in("list_tiles.txt"); // list of tiles
        for (int i = 0; i < MAX_NUM_TILES; ++i)
        {
            std::string name_tile;
            in >> name_tile;

            loadImage(tiles[theme_id][i], links + name_tile, -1);
        }

        in.close();
    }
}

void initProgram()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        printf("Warning: Linear texture filtering not enabled!");

    gWindow = SDL_CreateWindow("PikaJong 1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == NULL)
    {
        printf("gWindowcould not be created! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (gRenderer == NULL)
    {
        printf("gRenderer could not be created! SDL Error: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (IMG_Init(imgFlags) == 0 || imgFlags == 0)
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        exit(-1);
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(-1);
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(-1);
    }
}

void closeObject()
{

    // Destroy gWindowand gRenderer
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
