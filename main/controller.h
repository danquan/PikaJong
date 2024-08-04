/*
This class is used to control the main window, 
renderer, and handle events and all objects.
*/

#ifndef __SYSTEM_CONTROLLER_H
#define __SYSTEM_CONTROLLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <map>
#include <graphic/graphic.h>
#include <sound/sound.h>
#include <utils/jsonhelper.h>

enum EventStatus {
    SUCESS = 0,
    QUIT,
    ERROR,
};

class Controller
{
private:
    SDL_Window *gWindow; // Main Window
    SDL_Renderer *gRenderer; // Main gRenderer to Main Window

    /**
     * @brief List of graphic objects
     */
    std::map<std::string, Graphic*> listGraphic;

    /**
     * @brief List of sound objects
     */
    std::map<std::string, Sound*> listSound;

    /**
     * @brief List of theme
     */
    std::map<std::string, std::string> listTheme;

    /**
     * @brief List of Jong images
     */
    std::map<std::string, SDL_Texture*> listJong;

    /**
     * @brief Constructor of Controller
     * @note This constructor is private because Controller is a singleton class
     */
    Controller();
    ~Controller() {}

private:
    /**
     * @brief Path of assets
     */
    std::string ASSETS_PATH;

    /**
     * @brief set assets directory
     * @param assetPath path of assets
     * @return 0 if success
     */
    int setAssetPath(std::string assetPath) {
        ASSETS_PATH = assetPath;
        return 0;
    }

public:

    /*
     * @brief Get instance of Controller
     */
    static Controller& getInstance() {
        static Controller instance;
        return instance;
    }

    /**
     * @brief Init WINDOW, RENDERER and all objects
     * @return 0 if success, otherwise return error code
     */
    int setUp(std::string configPath);

    /**
     * @brief Init graphic objects
     * @param config Scheme of graphic objects
     * @return 0 if success
     */
    int initGraphicObjects(json config);

    /**
     * @brief Init sound objects
     * @param config Scheme of sound objects
     * @return 0 if success
     */
    int initSoundObjects(json config);

    /**
     * @brief Clear screen
     */
    void clearScreen();

    /**
     * @brief Quit window
     */
    void quit();

    /**
     * @brief Handle event
     * @return status code of event
     */
    EventStatus handleEvent(SDL_Event &e);

    /**
     * @brief Add graphic to list
     */
    void addGraphic(Graphic *graphic);

    /**
     * @brief Add sound to list
     */
    void addSound(Sound *sound);

    /**
     * @brief Render texture to screen
     * @param texture Texture to render
     * @param srcRect Source rectangle
     * @param dstRect Destination rectangle
     * @param colorTint RGB color of texture
     * @param alpha Alpha
     * @return 0 if success
     */
    int render( SDL_Texture *texture, 
                SDL_Rect *srcRect, 
                SDL_Rect *dstRect, 
                SDL_Color colorTint = {255, 255, 255}, 
                Uint8 alpha = 255
              );

    /**
     * @brief Process all objects
     * @note This function is called every game loop
     * @return 0 if success
     */
    int process();

    /**
     * @brief Render all objects
     * @return 0 if success
     */
    int present();
    
    /**
     * @brief Set theme for all objects
     * @param themePath name of theme
     */
    int setTheme(std::string theme);

    /**
     * @brief Set graphic theme
     * @param theme name of theme
     * @return 0 if success
     */
    int setGraphicTheme(json theme);

    /**
     * @brief Set sound theme
     * @param theme name of theme
     * @return 0 if success
     */
    int setSoundTheme(json theme);

    /**
     * @brief Load music
     * @param path path of music
     * @return Mix_Music object
     */
    Mix_Music* loadMusic(std::string path);

    /**
     * @brief Load Chunk
     * @param path path of Chunk
     * @return Mix_Chunk object
     */
    Mix_Chunk* loadChunk(std::string path);

    /**
     * @brief Load image
     * @param path path of image
     * @return SDL_Texture object of image
     */
    SDL_Texture* loadImage(std::string path);
};

#endif