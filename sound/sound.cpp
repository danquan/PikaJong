#include <sound.h>
#include <controller.h>

Sound::Sound(std::string name, int volume) {
    this->name = name;
    setVolume(volume);

    Controller::getInstance().addSound(this);
}

void Sound::setVolume(int volume) {
    currentVolume = volume;
    Mix_Volume(-1, volume);
}