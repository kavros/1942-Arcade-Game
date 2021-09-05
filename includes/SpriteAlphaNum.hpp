#ifndef SuperAlphaNum_hpp
#define SuperAlphaNum_hpp

#include "../includes/Sprite.hpp"
#include "../includes/includes.h"
#include "../includes/AnimationFilmHolder.hpp"

class SpriteAlphaNum :public Sprite{
    char _c;
public:
    SpriteAlphaNum(char c, int point_x, int point_y);
    char getChar(void) const;
    void setChar(char c);
};
#endif