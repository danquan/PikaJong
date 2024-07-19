#ifndef __CHUNK_H
#define __CHUNK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <sound.h>

class Chunk : public Sound
{
private:
    Mix_Chunk *chunk;
    int channel;

public:

    /**
     * @brief Constructor of Chunk
     * @param chunk Chunk file
     * @param name Name of Chunk
     * @param volume Volume of chunk
     * @param channel Channel where this chunk played on
     */
    Chunk(Mix_Chunk *chunk, std::string name, int volume = 0, int channel = -1);

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