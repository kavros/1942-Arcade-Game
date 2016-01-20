#include "SoundHolder.hpp"

SoundHolder* SoundHolder::holder = nullptr;

//constructor
SoundHolder::SoundHolder(){
    
}

//destructor
SoundHolder::~SoundHolder(){
    soundMap.clear();
}

SoundHolder* SoundHolder::getSoundHolder(){
    if(!holder){
        holder = new SoundHolder();
    }
    return holder;
}

void SoundHolder::initSounds(){
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("SDL MIXER Error: %s \n", SDL_GetError());
    }

    SoundHolder::addSound("gunshot", Mix_LoadWAV(  (string(SOUNDS_PATH) + string("gunshot.wav")).c_str()  ));

    if (! SoundHolder::getSound("gunshot") ){
        printf("Could not load gunshot.wav : %s \n", Mix_GetError());
    }

}


void SoundHolder::addSound(string id, Mix_Chunk* sound){
    SoundHolder::getSoundHolder()->soundMap[ id ] = sound;
}

Mix_Chunk* SoundHolder::getSound(string id){
    return SoundHolder::getSoundHolder()->soundMap[ id ];
}