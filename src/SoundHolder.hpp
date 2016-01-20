#ifndef SoundHolder_hpp
#define SoundHolder_hpp

#include "includes.h"

class SoundHolder{
private:
    typedef std::map<string, Mix_Chunk*> SoundMap;
    
    SoundMap soundMap;
    static SoundHolder* holder;
    
    //constructor
    SoundHolder();
    
    //destructor
    ~SoundHolder();
public:
    
    static SoundHolder* getSoundHolder();
    static void initSounds();
    static void addSound(string id, Mix_Chunk* sound);
    static Mix_Chunk* getSound(string id);
    
};

#endif
