#ifndef SuperAlphaNum_hpp
#define SuperAlphaNum_hpp

#include "Sprite.hpp"
#include "includes.h"
#include "AnimationFilmHolder.hpp"

class SpriteAlphaNum :public Sprite{
    char _c;
public:
    SpriteAlphaNum(char c, int point_x, int point_y);
    char getChar(void) const;
    void setChar(char c);
};
#endif