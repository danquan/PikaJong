#ifndef __CHUNK_H
#define __CHUNK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <sound/sound.h>

class Chunk : public Sound
{
private:
    Mix_Chunk *chunk;
    int channel;

public:

    /**
     * @brief Constructor of Chunk
     * @param name Name of Chunk
     * @param volume Volume of chunk
     * @param chunk Chunk file
     * @param channel Channel where this chunk played on
     */
    Chunk(std::string name, int volume = 0, Mix_Chunk *chunk = NULL, int channel = -1);

    /**
     * @brief Set the chunk file
     * @param chunk Chunk file
     * @return 0 if success
     */
    int setChunk(Mix_Chunk *chunk) {
        this->chunk = chunk;
        return 0;
    }

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