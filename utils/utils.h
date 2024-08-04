#ifndef __UTILS_H
#define __UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <graphic/graphic.h>

class ObjectDetector {
private:
    ObjectDetector();
public:
    static ObjectDetector& getInstance() {
        static ObjectDetector instance;
        return instance;
    }

    /**
     * @brief Check if the graphic object is a screen
     * @param graphicObject Graphic object to check
     * @return True if the graphic object is a screen, false otherwise
     */
    bool isScreen(Graphic* graphicObject);
};

#endif
