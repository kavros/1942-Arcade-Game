#include "SpriteAlphaNum.hpp"

SpriteAlphaNum::SpriteAlphaNum(char c,int point_x, int point_y): Sprite() {
    _c = c;
    AnimationFilmHolder* animationHolder=  AnimationFilmHolder::Get(); 
    
    
    /*SpriteType type = GAME_INFO;
    
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = 9;
    dstRect.h = 13;
    
    
    SDL_Point p;
    p.x = point_x;
    p.y = point_y;
    
    
    AnimationFilm* currFilm = animationHolder->GetFilm(string(1, c));
    Sprite(0, dstRect, p, true, type, currFilm);*/
    
    _type = GAME_INFO;
    
    _dstRect.x = point_x;
    _dstRect.y = point_y;
    _dstRect.w = 9;
    _dstRect.h = 13;
    
    _isVisible = true;
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