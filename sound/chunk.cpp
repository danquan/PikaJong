#include <sound/chunk.h>

Chunk::Chunk(std::string name, 
             int volume, 
             Mix_Chunk *chunk, 
             int channel
) : Sound(name, volume)
{
    this->chunk = chunk;
    this->channel = channel;
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