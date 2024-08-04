#ifndef __MUSIC_H
#define __MUSIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <sound/sound.h>

class Music : public Sound
{
private:
    Mix_Music *music;
public:

    /**
     * @brief Construct a new Music object
     * @param name The name of the music
     * @param volume The volume of the music
     * @param music The music object
     * @return Music object
     */
    Music(std::string name, int volume = 0, Mix_Music *music = NULL);

    /**
     * @brief Set the music object
     * @param music The music object
     * @return 0 if success
     */
    int setMusic(Mix_Music *music) {
        this->music = music;
        return 0;
    }

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