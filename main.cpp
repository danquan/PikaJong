#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "main.h"
#include "constant.h"
#include "definition.h"
#include "game_run.h"
#include "menu.h"

void run()
{
    assignLevel("1");
    createStartButton();

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

                if (currentScreen == GAME_SCREEN)
                    processGameMouseDown(x, y);
                else 
                    processMenuMouseDown(x, y);
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 255, 178, 102, 255);
        SDL_RenderClear(gRenderer);

        // Do something here
        if(currentScreen == MENU_SCREEN)
            menuRender(gRenderer);
        else if (currentScreen == GAME_SCREEN)
            gameRender(gRenderer);
        

        // Force Render
        SDL_RenderPresent(gRenderer);
    }
}

int main(int argc, char *argv[])
{
    initProgram();
    loadMedia();
    run();
    closeObject();
}

void loadMedia(type_Tiles typeCell)
{

    std::string links;
    /*If Type of tile is chosen, then assign links to be the directory; otherwise, choose it by randomizing*/
    {
        if (typeCell == BLACK_TILE)
            links = "images\\tiles\\Black\\";
        else if (typeCell == REGULAR_TILE)
            links = "images\\tiles\\Regular\\";
        else
            links = (rand(1, 1000) & 1) ? "images\\tiles\\Black\\" : "images\\tiles\\Regular\\";
    }
    
    /*load highlight*/
    {
        SDL_Surface *tempChosen = IMG_Load((links + "chosen.png").c_str());
        if (tempChosen == NULL)
        {
            printf("Fail to load image %s\n", (links + "chosen.png").c_str());
            exit(-1);
        }

        chosen_Highlight = SDL_CreateTextureFromSurface(gRenderer, tempChosen);
        SDL_SetTextureBlendMode(chosen_Highlight, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(chosen_Highlight, 125);

        if (chosen_Highlight == NULL)
        {
            printf("Fail to create texture from image %s\n", (links + "chosen.png").c_str());
            exit(-1);
        }
    }

    /*load win Screen*/
    {
        SDL_Surface *tempWin = IMG_Load("images\\win.png");
        if (tempWin == NULL)
        {
            printf("Fail to load image %s\n", "images\\win.png");
            exit(-1);
        }

        SDL_Texture *temp_Win_Screen = SDL_CreateTextureFromSurface(gRenderer, tempWin);

        if (temp_Win_Screen == NULL)
        {
            printf("Fail to create texture from image %s\n", "images\\win.png");
            exit(-1);
        }

        win_Screen.assignTexture(temp_Win_Screen, tempWin->w, tempWin->h);
    }

    /*load Button*/
    {
        SDL_Surface *tempButton = IMG_Load("images\\start_Button.png");
        if (tempButton == NULL)
        {
            printf("Fail to load image %s\n", "images\\start_Button.png");
            exit(-1);
        }

        SDL_Texture *temp_Button_texture = SDL_CreateTextureFromSurface(gRenderer, tempButton);

        if (temp_Button_texture == NULL)
        {
            printf("Fail to create texture from image %s\n", "images\\start_Button.png");
            exit(-1);
        }

        startButton.assignTexture(temp_Button_texture, tempButton->w, tempButton->h);
    }

    /* load all image */
    std::ifstream in("list_tiles.txt"); // list of tiles
    for (int i = 0; i < MAX_NUM_TILES; ++i)
    {

        std::string name_tile;
        in >> name_tile;

        /*Load tile content*/
        SDL_Surface *tempTile = IMG_Load((links + name_tile).c_str());
        if (tempTile == NULL)
        {
            printf("Fail to load image %s\n", (links + name_tile).c_str());
            exit(-1);
        }

        /*Load tile background*/
        SDL_Surface *tempBackground = IMG_Load((links + "Front.png").c_str());
        if (tempBackground == NULL)
        {
            printf("Fail to load background %s\n", (links + "Front.png").c_str());
            exit(-1);
        }

        /*"Print" content on background*/
        SDL_Rect dstRect = {(tempBackground->w - 480) / 2, (tempBackground->h - 640) / 2, 480, 640};
        SDL_BlitScaled(tempTile, NULL, tempBackground, &dstRect);

        /*Create texture to render*/
        SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(gRenderer, tempBackground);
        if (tempTexture == NULL)
        {
            printf("Fail to create texture from image %s\n", (links + name_tile).c_str());
            exit(-1);
        }
        /*Assign texture here*/
        tile[i].assignTexture(tempTexture, tempBackground->w, tempBackground->h);

        // Free memory
        SDL_FreeSurface(tempTile);
        SDL_FreeSurface(tempBackground);
    }

    in.close();
}

void initProgram()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
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
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}