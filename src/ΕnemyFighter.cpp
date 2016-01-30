#include "EnemyFighter.hpp"

unsigned _enemyFighterWidth;
unsigned _enemyFighterHeight;


EnemyFighter::EnemyFighter(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm, enum EnemyFighterType e,unsigned remainingBullets){
    assert( type == ALIEN_SHIP );
    
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
    setEnemyFireEnable(true);
    this->remainingBullets = remainingBullets;
    
    AnimationFilm* animationEnemyBulletFilm = AnimationFilmHolder::Get()->GetFilm("bullets");

    _enemyBulletDstRect.x=this->getDstRect().x + (this->_enemyFighterWidth/4);
    _enemyBulletDstRect.y=this->getDstRect().y + this->_enemyFighterHeight;
    _enemyBulletDstRect.w=animationEnemyBulletFilm->getFrameBox(0).w * Game::getSpriteSize() *2;
    _enemyBulletDstRect.h=animationEnemyBulletFilm->getFrameBox(0).h * Game::getSpriteSize()*2;
    _enemyType = e;
    this->addCollisionHandler(Sprite::touchHandler());
    
    SpritesHolder::getSpritesHolder()->add(this);
    
}

enum EnemyFighterType EnemyFighter::getEnemyFighterType(){
    return _enemyType;
}

unsigned EnemyFighter::getEnemyFighterWidth(){
    return _enemyFighterWidth;
}

unsigned EnemyFighter::getEnemyFighterHeight(){
    return _enemyFighterHeight;
}

void EnemyFighter::setFrame(unsigned i) {
    assert(0 < i < _currFilm->getTotalFrames());
    _frameNo = i;
    if(_enemyType != EnemyFighterType(RED_PLANE)){
        _dstRect.h = _currFilm->getFrameBox(_frameNo).h * Game::getSpriteSize();
        _dstRect.w = _currFilm->getFrameBox(_frameNo).w * Game::getSpriteSize();
    }
}

void EnemyFighter::setEnemyFireEnable(bool fire){
    enemyFireEnable = fire;
}

SDL_Rect EnemyFighter::getEnemyBulletDstRect(int frame){

    _enemyBulletDstRect.x=(this->getDstRect().x + this->getDstRect().w/2 - _enemyBulletDstRect.w/2);
    _enemyBulletDstRect.y=this->getDstRect().y + this->getEnemyFighterHeight()/3;

    return _enemyBulletDstRect;
}

bool EnemyFighter::getEnemyFireEnable(){
    return enemyFireEnable;
}

void EnemyFighter::fire(void){

    if( remainingBullets == 0)
        return;
    
    remainingBullets--;
    
    static string str = "enemyFire";
    static int number = 0;
    string spriteEnemyFireId = str + std::to_string (number);
    number++;
    
    /*bullet test*/
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    Sprite* enemyBullet = new Sprite(spriteEnemyFireId, 0, getEnemyBulletDstRect(0), {0,0}, true, ALIEN_SHIP, fireAnimationFilm);
    assert(enemyBullet);
    
    //play sound for fire
    SoundHolder::playSound("gunshot");
    
    //fireAnimation
    Animation* fireAnimation = AnimationHolder::getAnimationHolder()->getAnimation("enemyFire");
    assert(fireAnimation);
    
    MovingAnimator* fireAnimator = new MovingAnimator("animatorFire", enemyBullet, (MovingAnimation*)fireAnimation);
    
    AnimatorHolder::Register(fireAnimator);
    
    fireAnimator->start(Game::getGameTime());
    
    enemyBullet->addCollisionHandler(Sprite::fireHandler());
    
    /*bullet test end*/
}

void EnemyFighter::createPowerUp(){
    AnimationFilm* powerUpAnimationFilm = AnimationFilmHolder::Get()->GetFilm("powerUps");
    assert(powerUpAnimationFilm);
    Sprite* powerUp;
    
    PowerUpType powerUpType = PowerUpType(Game::getNextPowerUpType());
    unsigned powerUpFrameNo = powerUpType;

	powerUp = new PowerUp("powerUpSprite", powerUpType, powerUpFrameNo, { getDstRect().x, getDstRect().y, getDstRect().w, getDstRect().h }, { 0, 0 }, true, POWER_UPS, powerUpAnimationFilm);

    assert(powerUp);
    
    powerUp->addCollisionHandler(Sprite::touchPowerUpHandler());
    
    //play sound for fire
    //SoundHolder::playSound("gunshot");
    
    //powerUpAnimation
    Animation* powerUpAnimation = AnimationHolder::getAnimationHolder()->getAnimation("powerUp");
    assert(powerUpAnimation);

    //powerUpAnimator
    MovingAnimator* powerUpAnimator = new MovingAnimator("powerUpAnimator", powerUp, (MovingAnimation*)powerUpAnimation);
    assert(powerUpAnimator);
    
    AnimatorHolder::Register(powerUpAnimator);
    powerUpAnimator->start(Game::getGameTime());
    
}