#include "SpriteString.hpp"

SpriteString::SpriteString(string str,int x, int y){
    int nx = x, ny = y;
    for (int n = 0; n < str.size(); n++)
    {
        SpriteAlphaNum* san = new SpriteAlphaNum(str[n],nx,ny);
        nx += san->getCurrFilm()->getFrameBox(0).w;
        nx += 2;
        ny += san->getCurrFilm()->getFrameBox(0).y;
        // cout<< "nx: " << nx << " ny: "<< ny <<" Char: "<< str[n]<<std::endl;
        spriteString.push_back(san);
        SpritesHolder::getSpritesHolder()->add(san);
    }
    
}


/*SpriteString::~SpriteString(){
 
 for(int i=0; i < getSizeOfSpriteString();i++){
 delete getSpriteAlphaNum(i);
 }
 }*/

void SpriteString::changeString(string str,int x, int y){
    int nx = x, ny = y;
    SpriteAlphaNum* san;
    AnimationFilmHolder* animationHolder=  AnimationFilmHolder::Get();
    for( int n = 0; n < spriteString.size(); n++){
        san = getSpriteAlphaNum(n);
        san->setVisibility(false);
    }
    nx = x;
    ny = y;
    for (int n = 0; n < str.size(); n++)
    {
       
        if(n >= spriteString.size()){
            san = new SpriteAlphaNum(str[n],nx,ny);
            spriteString.push_back(san);
            SpritesHolder::getSpritesHolder()->add(san);
        }else{
            san = getSpriteAlphaNum(n);
            AnimationFilm * currFilm = animationHolder->GetFilm(string(1, str[n]));
            san->setCurrFilm(currFilm);
            san->setDstRectX(nx);
            san->setDstRectY(ny);
        }
        san->setVisibility(true);
        nx += san->getCurrFilm()->getFrameBox(0).w;
        nx += 2;
        ny += san->getCurrFilm()->getFrameBox(0).y;
        //cout<< "nx: " << nx << " ny: "<< ny <<" Char: "<< str[n]<<std::endl;
        //spriteString.push_back(san);
        //SpritesHolder::getSpritesHolder()->add(san);
    }
}

SpriteAlphaNum* SpriteString::getSpriteAlphaNum(unsigned i) const{
    return spriteString[i];
}

void SpriteString::addSpriteAlphaNum(SpriteAlphaNum* san) {
    spriteString.push_back(san);
}

unsigned long SpriteString::getSizeOfSpriteString(void) const{
    return spriteString.size();
}

unsigned long SpriteString::getSize(){
	return spriteString.size();
	
}