#ifndef __CHUNK_H
#define __CHUNK_H

#if defined(_WIN64) || defined(_WIN32)
#include <SDL.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <string>
#include <sound.h>

class Chunk : public Sound
{
private:
    Mix_Chunk *chunk;
    int channel;

public:
    Chunk(int chanel = -1, Mix_Chunk *chunk, std::string name, int volume = 0);

    /**
     * @brief Set the volume of the sound
     */
    virtual void setVolume(int volume);

    /**
     * @brief Play the sound
     * @param numLoop The number of loops
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