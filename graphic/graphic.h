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
    /**
     * @brief Constructor of the graphic
     * @param name Name of the graphic
     * @param position Position of the graphic
     * @note This constructor is protected because Graphic is an abstract class
     */
    Graphic(std::string name, SDL_Rect position);

    /**
     * @brief Name of the graphic
     */
    std::string name;

    /**
     * @brief Childs of the graphic:
     * Childs are graphics that are rendered inside this graphic. 
     */
    std::vector<Graphic*> childs;

    /**
     * @brief Parents of the graphic:
     * Parents are graphics that this graphic is rendered inside.
     */
    std::vector<Graphic*> parents;

    /**
     * @brief Position of the graphic
     * @note Including coordinates and size of the graphic
     */
    SDL_Rect position;

    /**
     * @brief Check if graphic is active:
     * `true` if active, `false` otherwise
     */
    bool graphicActive;

public:
    /**
     * @brief Get the name of the graphic
     * @return The name of the graphic
     */
    std::string getName() {
        return name;
    }

    /**
     * @brief Process this object and all its child each gameloop
     * @return 0 if success
     */
    virtual int process();

    /*
     * @brief Render the graphic
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