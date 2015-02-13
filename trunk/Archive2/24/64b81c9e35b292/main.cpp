#include <iostream>
#include <vector>
#include <algorithm>

enum class SoundId { Invalid = -1 };

SoundId createSound()
{
    return static_cast<SoundId>(1);
}

void destroySound(SoundId /*sound*/)
{
}

enum class SpriteId { Invalid = -1 };

SpriteId createSprite()
{
    return static_cast<SpriteId>(2);
}

void destroySprite(SpriteId /*sprite*/)
{
}


int main(...)
{
    SoundId sound = createSound();
    SpriteId sprite = createSprite();
    // destroySound(sprite); // cannote convert SpriteId to SoundIf for argument 1 of destroySound
    destroySprite(sprite);
    destroySound(sound);
}