#ifndef Power_Up_hpp
#define Power_Up_hpp

#include "../includes/includes.h"

#include "../includes/Sprite.hpp"
#include "../includes/AnimationFilm.hpp"
#include "../includes/AnimationFilmHolder.hpp"
#include "../includes/SpritesHolder.hpp"
#include "../includes/MovingAnimator.h"
#include "../includes/AnimationHolder.h"
#include "../includes/Game.hpp"

#define POWER_UP_TYPE_SIZE 7

enum PowerUpType {
    QUAD_GUN = 0,
    ENEMY_CRASH,
    SIDE_FIGHTERS,
    EXTRA_LIFE,
    NO_ENEMY_BULLETS,
    EXTRA_LOOP,
    THOUSAND_POINTS
};

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
    static void enableEnemyFire();

};

#endif