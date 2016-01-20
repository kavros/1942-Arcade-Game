#include "SpriteAlphaNum.hpp"

SpriteAlphaNum::SpriteAlphaNum(char c,int point_x, int point_y): Sprite() {
    _c = c;
    AnimationFilmHolder* animationHolder=  AnimationFilmHolder::Get(); 

    _type = GAME_INFO;
    
    _dstRect.x = point_x;
    _dstRect.y = point_y;
    _dstRect.w = 9;
    _dstRect.h = 13;
    
    setVisibility(true);
    _frameNo = 0;
    
    _point.x = point_x;
    _point.y = point_y;
    _currFilm = animationHolder->GetFilm(string(1, c));
}
char SpriteAlphaNum::getChar(void) const{
    return _c;
}
void SpriteAlphaNum::setChar(char c){
    AnimationFilmHolder* animationHolder=  AnimationFilmHolder::Get();
    AnimationFilm* currFilm = animationHolder->GetFilm(string(1, c));
    setCurrFilm(currFilm);
}