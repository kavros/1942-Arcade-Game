#ifndef EnemyFighter_hpp
#define EnemyFighter_hpp

#include "includes.h"

#include "Sprite.hpp"
#include "AnimationFilm.hpp"
#include "AnimationFilmHolder.hpp"
#include "SpritesHolder.hpp"
#include "MovingAnimator.h"
#include "AnimationHolder.h"
#include "Game.hpp"

class EnemyFighter:public Sprite{
    
private:
    unsigned _enemyFighterWidth;
    unsigned _enemyFighterHeight;
    SDL_Rect _enemyBulletDstRect;

public:
    
    //constructor
    EnemyFighter(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm);
    
    //get
    unsigned getEnemyFighterWidth();
    unsigned getEnemyFighterHeight();
    SDL_Rect getEnemyBulletDstRect(int frame);

    //set

    //functionallity
    void fire(void);
    
};

#endif