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
    
    static SoundHolder* getSoundHolder();
    
    static void addSound(string id, Mix_Chunk* sound);

public:

    static void initSounds();
    static Mix_Chunk* getSound(string id);
    static void cleanUp();
    static void playSound(string id);
};

#endif
