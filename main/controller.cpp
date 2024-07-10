#include <controller.h>
#include <json.h>
#include <fstream>

using json = nlohmann::json;

Controller::Controller() {
    gWindow = NULL;
    gRenderer = NULL;
}

int Controller::setUp(std::string configPath) {
    // load config
    std::ifstream configFile(configPath);
    if (!configFile.is_open())
    {
        printf("Could not open config file\n");
        return 1;
    }
    json config;
    configFile >> config;
    configFile.close();

    std::string windowName = config["program"];
    int SCREEN_WIDTH = config["screen"]["width"];
    int SCREEN_HEIGHT = config["screen"]["height"];

    // create window
    gWindow = SDL_CreateWindow(windowName.c_str(), 
                               SDL_WINDOWPOS_UNDEFINED, 
                               SDL_WINDOWPOS_UNDEFINED, 
                               SCREEN_WIDTH, SCREEN_HEIGHT, 
                               SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // create renderer on gWindow
    gRenderer = SDL_CreateRenderer(gWindow, 
                                   -1, 
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL) {
        printf("renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return 2;
    }
    
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return 0;
}

void Controller::clearScreen() {
    SDL_SetRenderDrawColor(gRenderer, 255, 178, 102, 255);
    SDL_RenderClear(gRenderer);
}

void Controller::quit() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
}

EventStatus Controller::handleEvent(SDL_Event &e) {
    if (e.type == SDL_QUIT) {
        return QUIT;
    }
}

void Controller::addGraphic(Graphic *graphic) {
    listGraphic[graphic->getName()] = graphic;
}

void Controller::addSound(Sound *sound) {
    listSound[sound->getName()] = sound;
}

int Controller::render(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect) {
    if (SDL_RenderCopy(gRenderer, texture, srcRect, dstRect) != 0) {
        printf("Could not render texture! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}