#ifndef __SOUND_H
#define __SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>

struct Sound
{
protected:
    std::string name;
    int currentVolume;

    Sound(std::string name, int volume = 0);
public:

    /**
     * @brief Get the name of the sound
     * @return The name of the sound
     */
    std::string getName() {
        return name;
    }
    
    /**
     * @brief Set the volume of the sound
     */
    void setVolume(int volume);

    /**
     * @brief Play the sound
     * @param isLoop The number of loops
     */
    virtual void play(int numLoop);

    /**
     * @brief Pause the sound
     */
    virtual void pause();

    /**
     * @brief Stop the sound
     */
    virtual void stop();
};

#endif