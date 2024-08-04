#include "main.h"
#include "controller.h"

int gameLoop() {
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        EventStatus status = Controller::getInstance().handleEvent(e);
        if (status != SUCESS) {
            return (int)status;
        }
    }

    if (!Controller::getInstance().process()) {
        return 1;
    }

    Controller::getInstance().clearScreen();
    Controller::getInstance().present();

    return 0;
}

int main(int argc, char *argv[])
{
    if (initProgram() != 0) {
        closeObject();
        return -1;
    }

    do {
        
    } while (gameLoop() == 0);

    closeObject();
    return 0;
}

int initProgram()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (IMG_Init(imgFlags) == 0 || imgFlags == 0) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 2;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 3;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 4;
    }

    if (Controller::getInstance().setUp(CONFIG_PATH) != 0) {
        return 5;
    }

    return 0;
}

void closeObject() {
    // Destroy gWindowand gRenderer
    Controller::getInstance().quit();

    // Quit SDL subsystems
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
