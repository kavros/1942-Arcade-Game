#ifndef SpriteString_hpp
#define SpriteString_hpp

#include "../includes/includes.h"
#include "../includes/SpriteAlphaNum.hpp"
#include "../includes/SpritesHolder.hpp"
#include "../includes/AnimationFilmHolder.hpp"
#include "../includes/SoundHolder.hpp"

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
    bool getVisibility();

    //set
    void addSpriteAlphaNum(SpriteAlphaNum* san) ;
    void setVisibility(bool visibility);
    
    //accessor
    void changeString(string str,int x, int y);

};

#endif