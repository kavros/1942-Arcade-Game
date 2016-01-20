#ifndef SpriteStringHolder_hpp
#define SpriteStringHolder_hpp

#include "includes.h"
#include "SpriteString.hpp"

class SpriteStringHolder{
private:
    typedef std::map<string, SpriteString*> SpriteStringMap;
    
    SpriteStringMap spriteStringMap;
    SpriteStringHolder* holder;
    
public:
};

#endif