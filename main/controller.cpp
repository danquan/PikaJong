#include <main/controller.h>
#include <graphic/screen.h>
#include <graphic/button.h>
#include <sound/music.h>
#include <sound/chunk.h>
#include <utils/jsonhelper.h>
#include <utils/utils.h>

Controller::Controller() {
    gWindow = NULL;
    gRenderer = NULL;
}

int Controller::setUp(std::string configPath) {
    // load config
    json config = JsonHelper::getInstance().loadJson(configPath);

    printf("Config loaded sucessfully!!!!\n", configPath.c_str());

    std::string windowName = config["program"].get<std::string>();
    int SCREEN_WIDTH = config["window"]["width"].get<int>();
    int SCREEN_HEIGHT = config["window"]["height"].get<int>();

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

    printf("Window and renderer created successfully, window size is %d x %d!!!\n",
                                                                     SCREEN_WIDTH, 
                                                                     SCREEN_HEIGHT);

    // Init objects
    if (initGraphicObjects(config["graphic"]) != 0) {
        printf("Could not init graphic objects!!!\n");
        return 3;
    }

    if (initSoundObjects(config["sound"]) != 0) {
        printf("Could not init graphic objects!!!\n");
        return 4;
    }

    // Init theme
    {
        setAssetPath(config["theme"]["path"].get<std::string>());
        json themes = config["theme"]["all"];
        for (auto it = themes.begin(); it != themes.end(); it++) {
            json theme = *it;
            listTheme[theme["name"]] = theme["path"];
        }
    }

    // Set theme

    if (setTheme(config["theme"]["default"].get<std::string>()) != 0) {
        printf("Could not set initial theme!!!\n");
        return 5;
    }

    printf("Initiation successful!!!\n");

    return 0;
}

int Controller::initGraphicObjects(json config) {
    // Init graphic objects
    json screenObj = config["screen"];
    for (auto it = screenObj.begin(); it != screenObj.end(); it++) {
        json scr = *it;
        Graphic *screen = new Screen(scr["name"].get<std::string>());

        if (scr.find("actived") != scr.end() && scr["actived"].get<bool>())
        {
            screen->active();
        }
        else
        {
            screen->deactive();
        }
    }

    json buttonObj = config["button"];
    for (auto it = buttonObj.begin(); it != buttonObj.end(); it++)
    {
        json but = *it;
        Graphic *button = new Button(but["name"].get<std::string>());

        if (but.find("actived") != but.end() && but["actived"].get<bool>()) {
            button->active();
        } else {
            button->deactive();
        }
    }

    json canvasObj = config["canvas"];
    for (auto it = canvasObj.begin(); it != canvasObj.end(); it++)
    {
        json can = *it;
        Graphic *canvas = new Screen(can["name"].get<std::string>());

        if (can.find("actived") != can.end() && can["actived"].get<bool>()) {
            canvas->active();
        } else {
            canvas->deactive();
        }
    }

    // Add relationship between objects
    for (auto it = screenObj.begin(); it != screenObj.end(); it++) {
        json scr = *it;

        Graphic *screen = listGraphic[scr["name"].get<std::string>()];

        for (auto it2 = scr["child"].begin(); it2 != scr["child"].end(); it2++) {

            screen->addChild(listGraphic[it2->get<std::string>()]);
            listGraphic[it2->get<std::string>()]->setParent(screen);
        }
    }

    for (auto it = buttonObj.begin(); it != buttonObj.end(); it++) {
        json but = *it;

        Graphic *button = listGraphic[but["name"].get<std::string>()];

        for (auto it2 = but["child"].begin(); it2 != but["child"].end(); it2++) {
            button->addChild(listGraphic[it2->get<std::string>()]);
            listGraphic[it2->get<std::string>()]->setParent(button);
        }
    }

    for (auto it = canvasObj.begin(); it != canvasObj.end(); it++) {
        json can = *it;

        Graphic *canvas = listGraphic[can["name"].get<std::string>()];

        for (auto it2 = can["child"].begin(); it2 != can["child"].end(); it2++) {
            canvas->addChild(listGraphic[it2->get<std::string>()]);
            listGraphic[it2->get<std::string>()]->setParent(canvas);
        }
    }

    return 0;
}

int Controller::initSoundObjects(json config) {
    json musicObj = config["music"];
    for (auto it = musicObj.begin(); it != musicObj.end(); it++) {
        json mus = *it;
        std::string name = mus["name"].get<std::string>();
        Sound *music = new Music(name);
        listSound[name] = music;
    }

    json chunkObj = config["chunk"];
    for (auto it = chunkObj.begin(); it != chunkObj.end(); it++) {
        json chu = *it;
        std::string name = chu["name"].get<std::string>();
        Sound *chunk = new Chunk(name);
        listSound[name] = chunk;
    }

    return 0;
}

int Controller::setTheme(std::string themeName) {
    json themeConfig = JsonHelper::getInstance().loadJson(listTheme[themeName]);

    if (setGraphicTheme(themeConfig["graphic"]) != 0) {
        printf("Could not set graphic theme for %s!!!\n", themeName.c_str());
        return 1;
    }

    if (setSoundTheme(themeConfig["sound"]) != 0) {
        printf("Could not set sound theme for %s!!!\n", themeName.c_str());
        return 2;
    }

    printf("Theme \"%s\" set successfully!!!\n", themeName.c_str());

    return 0;
}

int Controller::setGraphicTheme(json theme) {
    json screenTheme = theme["screen"];
    for (auto it = screenTheme.begin(); it != screenTheme.end(); it++) {
        json scr = *it;
        Screen *screen = dynamic_cast<Screen*>(listGraphic[scr["name"]]);

        screen->setBackground(loadImage(scr["background"].get<std::string>()));
        screen->setPosition({scr["position"]["x"].get<int>(),
                             scr["position"]["y"].get<int>(),
                             scr["position"]["width"].get<int>(),
                             scr["position"]["height"].get<int>()});
        screen->applyScale({scr["scale"]["x"].get<float>(), scr["scale"]["y"].get<float>()});
    }

    json buttonTheme = theme["button"];
    for (auto it = buttonTheme.begin(); it != buttonTheme.end(); it++) {
        json but = *it;
        Button *button = dynamic_cast<Button*>(listGraphic[but["name"]]);

        button->setTexture(loadImage(but["image"].get<std::string>()));
        button->setPosition({but["position"]["x"].get<int>(),
                             but["position"]["y"].get<int>(),
                             but["position"]["width"].get<int>(),
                             but["position"]["height"].get<int>()});
        button->applyScale({but["scale"]["x"].get<float>(), but["scale"]["y"].get<float>()});
    }

    json canvasTheme = theme["canvas"];
    for (auto it = canvasTheme.begin(); it != canvasTheme.end(); it++) {
        json can = *it;
        Screen *canvas = dynamic_cast<Screen *>(listGraphic[can["name"].get<std::string>()]);

        canvas->setPosition({can["position"]["x"].get<int>(),
                             can["position"]["y"].get<int>(),
                             can["position"]["width"].get<int>(),
                             can["position"]["height"].get<int>()});
        canvas->applyScale({can["scale"]["x"].get<float>(), can["scale"]["y"].get<float>()});    
    }


    json jong = theme["tile"]["jong"];

    for (auto it = jong.begin(); it != jong.end(); it++) {
        json jo = *it;
        listJong[jo["name"].get<std::string>()] = loadImage(jo["path"].get<std::string>()); 
    }
    
    return 0;
}

int Controller::setSoundTheme(json theme) {
    json musicTheme = theme["music"];
    for (auto it = musicTheme.begin(); it != musicTheme.end(); it++) {
        json mus = *it;
        dynamic_cast<Music*>(listSound[mus["name"].get<std::string>()])
                            ->setMusic(loadMusic(mus["path"].get<std::string>()));
    }

    json chunkTheme = theme["chunk"];
    for (auto it = chunkTheme.begin(); it != chunkTheme.end(); it++) {
        json chu = *it;
        dynamic_cast<Chunk*>(listSound[chu["name"].get<std::string>()])
                            ->setChunk(loadChunk(chu["path"].get<std::string>()));
    }

    return 0;
}

Mix_Music* Controller::loadMusic(std::string path) {
    Mix_Music *music = Mix_LoadMUS((ASSETS_PATH + "/" + path).c_str());

    if (music == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return NULL;
    }

    return music;
}

Mix_Chunk* Controller::loadChunk(std::string path) {
    Mix_Chunk *chunk = Mix_LoadWAV((ASSETS_PATH + "/" + path).c_str());

    if (chunk == NULL) {
        printf("Failed to load chunk! SDL_mixer Error: %s\n", Mix_GetError());
        return NULL;
    }

    return chunk;
}

SDL_Texture* Controller::loadImage(std::string path) {

    SDL_Surface *loadedSurface = IMG_Load((ASSETS_PATH + "/" + path).c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return NULL;
    } 

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
        printf("Unable to create texture from %s! SDL Error: %s\n", 
                                                        path.c_str(), 
                                                        SDL_GetError());
        return NULL;
    }
    SDL_FreeSurface(loadedSurface);

    return newTexture;
}

int Controller::process() {
    for (auto it = listGraphic.begin(); it != listGraphic.end(); it++) {
        if (it->second->isRoot()) {
            if (it->second->process()) {
                return 1;
            }
        }
    }

    return 0;
}

int Controller::present() {
    for (auto it = listGraphic.begin(); it != listGraphic.end(); it++) {
        if (it->second->isRoot()) {
            if (it->second->render()) {
                return 1;
            }
        }
    }
    SDL_RenderPresent(gRenderer);
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

int Controller::render(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect, SDL_Color colorTint, Uint8 alpha) {

    if (SDL_SetTextureColorMod(texture, colorTint.r, colorTint.g, colorTint.b) != 0) {
        printf("SDL_SetTextureColorMod");
        return 1;
    }

    if (SDL_SetTextureAlphaMod(texture, alpha) != 0) {
        printf("SDL_SetTextureAlphaMod");
        return 1;
    }

    if (SDL_RenderCopy(gRenderer, texture, srcRect, dstRect) != 0) {
        printf("Could not render texture! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}