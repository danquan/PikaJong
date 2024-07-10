#include <music.h>

Music::Music(Mix_Music *music, std::string name, int volume) : Sound(name, volume) {
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