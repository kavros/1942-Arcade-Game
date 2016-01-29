#include "PowerUp.hpp"

PowerUp::PowerUp(std::string id, PowerUpType _powerUpType, unsigned  _frameNo, SDL_Rect _dstRect,
                 SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm)
:Sprite(id, _frameNo, _dstRect, _point, _isVisible, _type, _currFilm){
    powerUpType = _powerUpType;
}

//get
PowerUpType PowerUp::getPowerUpType(){
    return powerUpType;
}

void PowerUp::activatePowerUp(Sprite* arg){
    switch ( getPowerUpType() ){
        case QUAD_GUN:
            //not ready
            assert(0);
            break;
        case ENEMY_CRASH:
            //not ready
            assert(0);
            break;
        case SIDE_FIGHTERS:{
            SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
            superAce->addSideFighters();
            break;
        }
        case EXTRA_LIFE:
            //not ready
            assert(0);
            break;
        case NO_ENEMY_BULLETS:
            //not ready
            assert(0);
            break;
        case EXTRA_LOOP:
            //not ready
            assert(0);
            break;
        case THOUSAND_POINTS:
            //not ready
            assert(0);
            break;
    }
}
