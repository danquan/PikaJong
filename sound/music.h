#ifndef __MUSIC_H
#define __MUSIC_H

#if defined(_WIN64) || defined(_WIN32)
    #include <SDL.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
#endif

#include <string>
#include <sound.h>

class Music : public Sound
{
private:
    Mix_Music *music;
public:
    Music(Mix_Music *music, std::string name, int volume = 0);

    /**
     * @brief Set the volume of the music
     */
    virtual void setVolume(int volume);

    /**
     * @brief Play the music
     * @param numLoop The number of loops
     */
    virtual void play(int numLoop);

    /**
     * @brief Pause the music
     */
    virtual void pause();

    /**
     * @brief Stop the music
     */
    virtual void stop();
};

#endif