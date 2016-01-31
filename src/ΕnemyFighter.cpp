#include "EnemyFighter.hpp"

EnemyFighter::EnemyFighter(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm, enum EnemyFighterType e,unsigned remainingBullets):
Sprite(id,frameNo,dstRect,point,isVisible,type,currFilm)
{
    assert( type == ALIEN_SHIP );
    
    _currFilm = currFilm;

    _dstRect = dstRect;
    _dstRect.h = currFilm->getFrameBox(frameNo).h;
    _dstRect.w = currFilm->getFrameBox(frameNo).w;
    
    _spriteId = id;
    _point = point;
    setVisibility(isVisible);
    _type = type;
    setFrame(frameNo);
    setState(STARTING);
    setEnemyFireEnable(true);
    _enemyType = e;

    this->remainingBullets = remainingBullets;
    
    setAnimationEnemyBulletFilm( AnimationFilmHolder::Get()->GetFilm("bullets") );
    
    //hardcoded
    
    _enemyBulletDstRect.x=this->getDstRect().x + (this->_enemyBulletDstRect.w/4);
    _enemyBulletDstRect.y=this->getDstRect().y + this->_enemyBulletDstRect.h;
    _enemyBulletDstRect.w= dstRect.w ;//_currFilm->getFrameBox(0).w;
    _enemyBulletDstRect.h= dstRect.h; //_currFilm->getFrameBox(0).h;
    //_enemyBulletDstRect.w=animationEnemyBulletFilm->getFrameBox(0).w * Game::getSpriteSize() *2;
   //_enemyBulletDstRect.h=animationEnemyBulletFilm->getFrameBox(0).h * Game::getSpriteSize()*2;
    _enemyBulletDstRect.x=10;
    _enemyBulletDstRect.y=10;
    _enemyBulletDstRect.w=10;
    _enemyBulletDstRect.h=10;
    
    //this->addCollisionHandler(Sprite::touchHandler());
    
    //SpritesHolder::getSpritesHolder()->add(this);
}

enum EnemyFighterType EnemyFighter::getEnemyFighterType(){
    return _enemyType;
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

    assert(!this->isOutOfWindow());
    
    //_enemyBulletDstRect.x=(this->getDstRect().x + this->getDstRect().w/2 - _enemyBulletDstRect.w/2);
    //_enemyBulletDstRect.y=this->getDstRect().y + this->getEnemyFighterHeight()/3;

    _enemyBulletDstRect.x=10;
    _enemyBulletDstRect.y=10;
    _enemyBulletDstRect.w=10;
    _enemyBulletDstRect.h=10;
    return _enemyBulletDstRect;
}

bool EnemyFighter::getEnemyFireEnable(){
    return enemyFireEnable;
}

AnimationFilm* EnemyFighter::getAnimationEnemyBulletFilm(){
    return this->animationEnemyBulletFilm;
}

void EnemyFighter::setAnimationEnemyBulletFilm(AnimationFilm* film){
    assert(film);
    this->animationEnemyBulletFilm = film;
}

void EnemyFighter::fire(void){
    /*
    if( remainingBullets == 0)
        return;
    
    remainingBullets--;
    */
    return;
    
    assert(this->isAlive() && !this->isOutOfWindow() && this->getVisibility());
    
    static int number = 0;
    string enemyFireId = "enemyFire_" + std::to_string (number);
    number++;
    
    cout << enemyFireId <<" fire\n";

    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    unsigned bulletFrameNo = 0;
    
    Sprite* enemyBullet = new Sprite(enemyFireId, bulletFrameNo, getEnemyBulletDstRect(bulletFrameNo), {0,0}, true, ALIEN_SHIP, fireAnimationFilm);
    assert(enemyBullet);
    assert(!enemyBullet->isOutOfWindow());
    //SpritesHolder::getSpritesHolder()->add(enemyBullet);
    
    //play sound for fire
    SoundHolder::playSound("gunshot");
    
    //fireAnimation
    Animation* fireAnimation = AnimationHolder::getAnimationHolder()->getAnimation("enemyFire");
    assert(fireAnimation);
    
    MovingAnimator* fireAnimator = new MovingAnimator(enemyFireId, enemyBullet, (MovingAnimation*)fireAnimation);
    assert(fireAnimator);
    
    AnimatorHolder::Register(fireAnimator);
    
    fireAnimator->start(Game::getGameTime());
    
   // enemyBullet->addCollisionHandler(Sprite::fireHandler());
    
    
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