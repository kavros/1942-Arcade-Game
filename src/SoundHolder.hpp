#ifndef SoundHolder_hpp
#define SoundHolder_hpp

#include "includes.h"
class SoundHolder{
private:
    typedef std::map<string, Mix_Chunk*> SoundMap;
    
    static bool _mute;
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
    static void setMute(bool m);
    static bool getMute();
    static Mix_Chunk* getSound(string id);
    static void cleanUp();
    static void playSound(string id);
};

#endif
