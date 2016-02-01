#include "EnemyFighter.hpp"

EnemyFighter::EnemyFighter(){
    //illegal use
    assert(0);
}

EnemyFighter::EnemyFighter(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm, enum EnemyFighterType e,unsigned remainingBullets):
Sprite(id,frameNo,dstRect,point,isVisible,type,currFilm)
{
    assert( type == ALIEN_SHIP );

    setEnemyFireEnable(true);
    setEnemyFighterType(e);
    
    setRemainingBullets(remainingBullets);
    
    setBulletFrame(0);
    
    setAnimationEnemyBulletFilm( AnimationFilmHolder::Get()->GetFilm("bullets") );
    
    enemyFighterLifes = 1;
    if( e == BIG_GREEN || e == BIG_GREY ){
        enemyFighterLifes = 3;
    }
    
    _enemyBulletDstRect.w = 8;
    _enemyBulletDstRect.h = 8;
    _enemyBulletDstRect.x=(this->getDstRect().x + this->getDstRect().w/2 - _enemyBulletDstRect.w/2);
    _enemyBulletDstRect.y=this->getDstRect().y + this->getDstRect().h;
    
    this->addCollisionHandler(Sprite::touchHandler());
    
}

unsigned EnemyFighter::getEnemyFighterLifes(){
    return this->enemyFighterLifes;
}

void EnemyFighter::setEnemyFighterLifes(unsigned lifes){
    this->enemyFighterLifes = lifes;
}

unsigned EnemyFighter::getBulletFrame(){
    return this->bulletFrame;
}

void EnemyFighter::setBulletFrame(unsigned frame){
    this->bulletFrame = frame;
}

unsigned EnemyFighter::getRemainingBullets(){
    return this->remainingBullets;
}

void EnemyFighter::setRemainingBullets(unsigned bullets){
    this->remainingBullets = bullets;
}

enum EnemyFighterType EnemyFighter::getEnemyFighterType(){
    return _enemyType;
}

void EnemyFighter::setFrame(unsigned i) {
    
    assert(0 < i < _currFilm->getTotalFrames());
    _frameNo = i;
    /*
    if(_enemyType != EnemyFighterType(RED_PLANE)){
        _dstRect.h = _currFilm->getFrameBox(_frameNo).h * Game::getSpriteSize();
        _dstRect.w = _currFilm->getFrameBox(_frameNo).w * Game::getSpriteSize();
    }
     */
}

void EnemyFighter::setEnemyFireEnable(bool fire){
    enemyFireEnable = fire;
}

void EnemyFighter::setEnemyFighterType(enum EnemyFighterType type){
    this->_enemyType = type;
}


SDL_Rect EnemyFighter::getEnemyBulletDstRect(){

    assert(!this->isOutOfWindow());

    _enemyBulletDstRect.x=(this->getDstRect().x + this->getDstRect().w/2 - _enemyBulletDstRect.w/2);
    _enemyBulletDstRect.y=this->getDstRect().y + this->getDstRect().h;
    
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

    if( !getEnemyFireEnable() || getRemainingBullets() == 0 ){
        return;
    }
    
    unsigned r = rand() % 3; // r in the range 0 to 2
        
    if( r == 1 ){
        setRemainingBullets( getRemainingBullets() - 1);
    }
    else{
        return;
    }
    
    assert(this->isAlive() && !this->isOutOfWindow() && this->getVisibility());
    
    static int number = 0;
    string spriteEnemyFireId = "spriteEnemyFire_" + std::to_string (number);
    string animatorEnemyFireId = "animatorEnemyFire_" + std::to_string (number);
    number++;
    
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);

    Sprite* enemyBullet = new EnemyFighter(spriteEnemyFireId, getBulletFrame(),getEnemyBulletDstRect() , {0,0}, true, ALIEN_SHIP, fireAnimationFilm,BULLET,0);
    
    assert(enemyBullet);
    
    //play sound for fire
    SoundHolder::playSound("gunshot");
    
    //fireAnimation
    Animation* fireAnimation = AnimationHolder::getAnimationHolder()->getAnimation("enemyFire");
    assert(fireAnimation);
    
    MovingAnimator* fireAnimator = new MovingAnimator(animatorEnemyFireId, enemyBullet, (MovingAnimation*)fireAnimation);
    assert(fireAnimator);
    
    fireAnimator->start(Game::getGameTime());
    
    enemyBullet->addCollisionHandler(Sprite::fireHandler());

}

void EnemyFighter::createPowerUp(){
    
    static int nameId=0;
    string spritePowerUpId = "spritePowerUpId" + std::to_string(nameId);
    string animatorPowerUpId = "animatorPowerUpId" + std::to_string(nameId);
    nameId++;
    
    AnimationFilm* powerUpAnimationFilm = AnimationFilmHolder::Get()->GetFilm("powerUps");
    assert(powerUpAnimationFilm);
    Sprite* powerUp;
    
    PowerUpType powerUpType = PowerUpType(Game::getNextPowerUpType());
    unsigned powerUpFrameNo = powerUpType;

	powerUp = new PowerUp(spritePowerUpId, powerUpType, powerUpFrameNo, { getDstRect().x, getDstRect().y, getDstRect().w, getDstRect().h }, { 0, 0 }, true, POWER_UPS, powerUpAnimationFilm);

    assert(powerUp);
    
    powerUp->addCollisionHandler(Sprite::touchPowerUpHandler());
    
    //play sound for power up
    //SoundHolder::playSound("gunshot");
    
    //powerUpAnimation
    Animation* powerUpAnimation = AnimationHolder::getAnimationHolder()->getAnimation("powerUp");
    assert(powerUpAnimation);

    //powerUpAnimator
    MovingAnimator* powerUpAnimator = new MovingAnimator(animatorPowerUpId, powerUp, (MovingAnimation*)powerUpAnimation);
    assert(powerUpAnimator);
    
    powerUpAnimator->start(Game::getGameTime());
    
}


