#ifndef SpriteStringHolder_hpp
#define SpriteStringHolder_hpp

#include "includes.h"
#include "SpriteString.hpp"

class SpriteStringHolder{
private:
    typedef std::map<string, SpriteString*> SpriteStringMap;
    
    SpriteStringMap spriteStringMap;
    static SpriteStringHolder* holder;
    
    //constructor
    SpriteStringHolder();
    
    //destructor
    ~SpriteStringHolder();
public:
    
    static SpriteStringHolder* getSpriteStringHolder();
    static void cleanup();
    static void addSpriteString(string id, SpriteString* spriteString);
    static SpriteString* getSpriteString(string id);

};

#endif