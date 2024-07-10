/*
This class is used to control the main window, 
renderer, and handle events and all objects.
*/

#ifndef __SYSTEM_CONTROLLER_H
#define __SYSTEM_CONTROLLER_H
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

#include <string>
#include <map>
#include <graphic.h>
#include <sound.h>

enum EventStatus {
    SUCESS = 0,
    QUIT,
    ERROR,
};

class Controller
{
private:
    static Controller *instance;
    SDL_Window *gWindow; // Main Window
    SDL_Renderer *gRenderer; // Main gRenderer to Main Window
    std::map<std::string, Graphic*> listGraphic;
    std::map<std::string, Sound*> listSound;
    Controller();
public:

    /*
     * @brief Get instance of Controller
     */
    static Controller getInstance() {
        if (instance == NULL) {
            instance = new Controller();
        }
        return *instance;
    }

    /*
     * @brief Init WINDOW, RENDERER
     * @return 0 if success, otherwise return error code
     */
    int setUp(std::string configPath);

    /*
     * @brief Show rendered objects on screen
     */
    void present() {
        SDL_RenderPresent(gRenderer);
    }

    /*
     * @brief Clear screen
     */
    void clearScreen();

    /*
     * @brief Quit window
     */
    void quit();

    /*
     * @brief Handle event
     * @return status code of event
     */
    EventStatus handleEvent(SDL_Event &e);

    /*
     * @brief Add graphic to list
     */
    void addGraphic(Graphic *graphic);

    /*
     * @brief Add sound to list
     */
    void addSound(Sound *sound);

    /**
     * @brief Render texture to screen
     * @param texture Texture to render
     * @param srcRect Source rectangle
     * @param dstRect Destination rectangle
     * @return 0 if success
     */
    int render(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect);
};

#endif