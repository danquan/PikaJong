#include <chunk.h>

Chunk::Chunk(int chanel, Mix_Chunk *chunk, std::string name, int volume) : Sound(name, volume) {
    this->chunk = chunk;
    this->channel = chanel;
}

void Chunk::setVolume(int volume) {
    Mix_Volume(channel, volume);
}

void Chunk::play(int numLoop) {
    Mix_PlayChannel(channel, chunk, numLoop);
}

void Chunk::pause() {
    Mix_Pause(-1);
}

void Chunk::stop() {
    Mix_HaltChannel(-1);
}