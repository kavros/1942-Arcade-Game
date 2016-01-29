#include "EnemyFighter.hpp"

unsigned _enemyFighterWidth;
unsigned _enemyFighterHeight;

EnemyFighter::EnemyFighter(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm){
    
    _spriteId = id;
    _dstRect = dstRect;
    _dstRect.h = currFilm->getFrameBox(frameNo).h;
    _dstRect.w = currFilm->getFrameBox(frameNo).w;
    _point = point;
    setVisibility(isVisible);
    _type = type;
    _currFilm = currFilm;
    setFrame(frameNo);
    _enemyFighterWidth= dstRect.w ;//_currFilm->getFrameBox(0).w;
    _enemyFighterHeight= dstRect.h; //_currFilm->getFrameBox(0).h;
    _state = STARTING;
    AnimationFilm* animationEnemyBulletFilm = AnimationFilmHolder::Get()->GetFilm("enemyBullets");
    
    _enemyBulletDstRect.x=this->getDstRect().x + (this->_enemyFighterWidth/4);
    _enemyBulletDstRect.y=this->getDstRect().y - this->_enemyFighterHeight;
    _enemyBulletDstRect.w=animationEnemyBulletFilm->getFrameBox(2).w * Game::getSpriteSize();
    _enemyBulletDstRect.h=animationEnemyBulletFilm->getFrameBox(2).h * Game::getSpriteSize();
    
    this->addCollisionHandler(Sprite::touchHandler());
    
    SpritesHolder::getSpritesHolder()->add(this);
    
}

void EnemyFighter::fire(void){
    static string str = "enemyFire";
    static int number = 0;
    string spriteEnemyFireId = str + std::to_string (number);
    number++;
    
    /*bullet test*/
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("enemyBullets");
    assert(fireAnimationFilm);
    
    Sprite* enemyBullet = new Sprite(spriteEnemyFireId, 2, _enemyBulletDstRect, {0,0}, true, ALIEN_SHIP, fireAnimationFilm);
    assert(enemyBullet);
    
    //play sound for fire
    SoundHolder::playSound("gunshot");
    
    //fireAnimation
    Animation* fireAnimation = AnimationHolder::getAnimationHolder()->getAnimation("animatorEnemyFire");
    assert(fireAnimation);
    
    MovingAnimator* fireAnimator = new MovingAnimator("animatorEnemyFire", enemyBullet, (MovingAnimation*)fireAnimation);
    
    AnimatorHolder::Register(fireAnimator);
    
    fireAnimator->start(Game::getGameTime());
    
    enemyBullet->addCollisionHandler(Sprite::fireHandler());
    
    /*bullet test end*/
    
}