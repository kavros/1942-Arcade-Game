#ifndef SpriteString_hpp
#define SpriteString_hpp

#include "includes.h"
#include "SpriteAlphaNum.hpp"
#include "SpritesHolder.hpp"
#include "AnimationFilmHolder.hpp"

class SpriteString {
    
private:
    std::vector <SpriteAlphaNum *> spriteString;
    
public:
    
    //constructor
    SpriteString(string str,int point_x, int point_y);
    
    //destructor
    ~SpriteString();
    
    //get
    SpriteAlphaNum* getSpriteAlphaNum(unsigned i) const;
    unsigned long getSizeOfSpriteString(void) const;
    unsigned long getSize();

    //set
    void addSpriteAlphaNum(SpriteAlphaNum* san) ;
    
    //accessor
    void changeString(string str,int x, int y);

};

#endif