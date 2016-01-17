
#include "includes.h"
#include "SpriteAlphaNum.hpp"
#include "SpritesHolder.hpp"
#include "AnimationFilmHolder.hpp"

class SpriteString {
    std::vector <SpriteAlphaNum *> spriteString;
public:
    SpriteString(string str,int point_x, int point_y);
    ~SpriteString();
    SpriteAlphaNum* getSpriteAlphaNum(unsigned i) const;
    
    void addSpriteAlphaNum(SpriteAlphaNum* san) ;
    
    unsigned long getSizeOfSpriteString(void) const;
    void changeString(string str,int x, int y);
};