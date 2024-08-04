#ifndef __GRAPHIC_H
#define __GRAPHIC_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

/*Vector in graphic*/
typedef struct SDL_RPoint
{
    double x;
    double y;
} SDL_Vector;

class Graphic
{
protected:
    /**
     * @brief Constructor of the graphic
     * @param name Name of the graphic
     * @param position Position of the graphic
     * @note This constructor is protected because Graphic is an abstract class
     */
    Graphic(std::string name, 
            SDL_Rect position = {0, 0, 0, 0}, 
            SDL_Vector scaleRate = {1, 1}, 
            SDL_Vector velocity = {0, 0}
    );

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
     * @brief Scale rate of the graphic
     * @note This is used to scale the graphic in the render process
     */
    SDL_Vector scaleRate;

    /**
     * @brief Velocity of the graphic in pixels per game loop
     */
    SDL_Vector velocity;

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
     * @brief Get the position of the graphic
     * @param position The position of the graphic
     * @return 0 if success
     */
    int setPosition(SDL_Rect position) {
        this->position = position;
        return 0;
    }

    /**
     * @brief Set scale rate of the graphic
     * @param scaleRate Scale rate of the graphic
     * @return 0 if success
     */
    int applyScale(SDL_Vector scaleRate) {
        this->scaleRate.x *= scaleRate.x;
        this->scaleRate.y *= scaleRate.y;
        return 0;
    }

    /**
     * @brief Check if the graphic is a root graphic (i.e. menu screen, ...)
     * @return `true` if the graphic is a root graphic, `false` otherwise
     */
    bool isRoot() {
        return parents.size() == 0;
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
     * @brief Set parent of graphic
     * @param parent Graphic to set
     * @return 0 if success
     */
    int setParent(Graphic* parent);
};

#endif