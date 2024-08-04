#include <sound/music.h>

Music::Music(std::string name, 
             int volume, 
             Mix_Music *music
) : Sound(name, volume)
{
    this->music = music;
}

void Music::setVolume(int volume) {
    Mix_VolumeMusic(volume);
}

void Music::play(int numLoop) {
    Mix_PlayMusic(music, numLoop);
}

void Music::pause() {
    Mix_PauseMusic();
}

void Music::stop() {
    Mix_HaltMusic();
}