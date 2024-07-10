#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#if defined(_WIN64) || defined(_WIN32)
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#endif

#include <string>
#include <vector>

class Graphic
{
protected:
    Graphic(std::string name, SDL_Rect position);
    std::string name;
    std::vector<Graphic*> childs, parents;
    SDL_Rect position;
    bool graphicActive;

public:
    /**
     * @brief Get the name of the graphic
     * @return The name of the graphic
     */
    std::string getName() {
        return name;
    }

    /*
     * @brief Render the graphic and all its child
     * @return 0 if success
     */
    virtual int render();

    /*
     * @brief Active object on screen
     */
    void active();

    /*
     * @brief Deactive object on screen
     */
    void deactive();

    /*
     * @brief Check if object is active
     * @return `true` if active, `false` otherwise
     */
    bool isActive() {
        return graphicActive;
    }
    
    /*
     * @brief Add child to graphic
     * @param child Graphic to add
     * @return 0 if success
     */
    int addChild(Graphic* child);

    /*
     * @brief Remove child from graphic
     * @param child Graphic to remove
     * @return 0 if success
     */
    int removeChild(Graphic* child);
};

#endif