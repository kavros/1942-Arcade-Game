/*
powerUp = new PowerUp("explosionSprite",QUAD_GUN, i, { 100 , i*60, powerUpAnimationFilm->getFrameBox(i).w , powerUpAnimationFilm->getFrameBox(i).h}, {0,0}, true, POWER_UPS, powerUpAnimationFilm);

((PowerUp*)powerUp)->activatePowerUp(arg);
*/

#ifndef Power_Up_hpp
#define Power_Up_hpp

#include "includes.h"

#include "Sprite.hpp"
#include "AnimationFilm.hpp"
#include "AnimationFilmHolder.hpp"
#include "SpritesHolder.hpp"
#include "MovingAnimator.h"
#include "AnimationHolder.h"
#include "Game.hpp"

#define POWER_UP_TYPE_SIZE 7

typedef enum PowerUpType {
    QUAD_GUN = 0,
    ENEMY_CRASH,
    SIDE_FIGHTERS,
    EXTRA_LIFE,
    NO_ENEMY_BULLETS,
    EXTRA_LOOP,
    THOUSAND_POINTS
}PowerUpType;

class PowerUp:public Sprite{
    
private:
    PowerUpType powerUpType;
public:
    
    //constructor
    PowerUp(std::string id, PowerUpType _powerUpType, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm);
    
    //get
    PowerUpType getPowerUpType();

    //set
    
    //functionallity
    void activatePowerUp(Sprite* arg);

};

#endif