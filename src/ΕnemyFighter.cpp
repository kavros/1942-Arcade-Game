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

    if( e == MED_GREEN_DOUBLE_ENG || e==MED_GREEN_ONE_ENG || e==MED_GREEN_TRIPLE_ENG){
        enemyFighterLifes = 3;
    }
    else if( e == MED_GREY_DOUBLE_ENG || e==MED_GREY_ONE_ENG || e==MED_GREY_TRIPLE_ENG || e==DEATH_STAR){
        enemyFighterLifes = 4;
    }
    else if( e == BIG_GREEN ){
        enemyFighterLifes = 8;
    }
    else if(e == BIG_GREY){
        enemyFighterLifes = 10;
    }
    else{
        enemyFighterLifes = 1;
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

void EnemyFighter::fireStraightBullet(){
    static int number = 0;
    string spriteEnemyFireId = "spriteEnemyFire" + std::to_string (number);
    string animatorEnemyFireId = "animatorEnemyFire" + std::to_string (number);
    number++;
    
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    Sprite* enemyBullet = new EnemyFighter(spriteEnemyFireId, getBulletFrame(),getEnemyBulletDstRect() , {0,0}, true, ALIEN_SHIP, fireAnimationFilm,BULLET,0);
    
    assert(enemyBullet);
    
    //play sound for fire
    SoundHolder::playSound("gunshot");
    
    //fireAnimation
    MovingAnimation* fireAnimation = (MovingAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("enemyFire");
    assert(fireAnimation);
    
    MovingAnimator* fireAnimator = new MovingAnimator(animatorEnemyFireId, enemyBullet, fireAnimation);
    assert(fireAnimator);
    
    fireAnimator->start(Game::getGameTime());
    
    enemyBullet->addCollisionHandler(Sprite::fireHandler());
}




void EnemyFighter::fireSideBullet(std::string id){
    assert(this->isAlive() && !this->isOutOfWindow() && this->getVisibility());
    
    static int number = 0;
    string spriteEnemySideLeftFireId = "sprite"+ id+  std::to_string (number);
    string animatorEnemySideLeftFireId = "animator"+ id + std::to_string (number);
    number++;
    
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    Sprite* spriteEnemySideLeftFire = new EnemyFighter(spriteEnemySideLeftFireId, getBulletFrame(),getEnemyBulletDstRect() , {0,0}, true, ALIEN_SHIP, fireAnimationFilm,BULLET,0);
    assert(spriteEnemySideLeftFire);
    
    //play sound for fire
    SoundHolder::playSound("gunshot");
    
    //fireAnimation
    MovingPathAnimation* fireLeftAnimation = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation(id);
    assert(fireLeftAnimation);

    MovingPathAnimator* fireLeftAnimator = new MovingPathAnimator(animatorEnemySideLeftFireId, spriteEnemySideLeftFire, (MovingPathAnimation*)fireLeftAnimation);
    assert(fireLeftAnimator);
    
    fireLeftAnimator->start(Game::getGameTime());
    
    spriteEnemySideLeftFire->addCollisionHandler(Sprite::fireHandler());
    
}

void EnemyFighter::fire(void){

    if( !getEnemyFireEnable() || getRemainingBullets() == 0 ){
        return;
    }
    
    if(this->getEnemyFighterType() == DEATH_STAR ){
        if(getFrame() == 0) fireStraightBullet();
        if(getFrame() == 3) fireSideBullet("EnemySideLeftFire");
        if(getFrame() == 6) fireSideBullet("EnemySideRightFire");

        setRemainingBullets( getRemainingBullets() - 1);        
        return;
    }
    
    unsigned r = rand() % 10; // r in the range 0 to 2

    if( r<2 ){
        if( this->getEnemyFighterType() == BIG_GREEN  ){
            if( getRemainingBullets() >= 3 ){
                setRemainingBullets( getRemainingBullets() - 3);
                fireSideBullet("EnemySideRightFire");
                fireSideBullet("EnemySideLeftFire");
            }
            else{
                return;
            }
        }else if(this->getEnemyFighterType() == BIG_GREY){
            if( getRemainingBullets() >= 5 ){
                setRemainingBullets( getRemainingBullets() - 5);
                fireSideBullet("EnemySideLeftFire");
                fireSideBullet("EnemySideRightFire");
                fireSideBullet("EnemySideLeftLeftFire");
                fireSideBullet("EnemySideRightRightFire");
            }
            else{
                return;
            }
        }
        else{
            setRemainingBullets( getRemainingBullets() - 1);
        }
    }
    else{
        return;
    }
    
    assert(this->isAlive() && !this->isOutOfWindow() && this->getVisibility());
    
    fireStraightBullet();

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

	powerUp = new PowerUp(spritePowerUpId, powerUpType, powerUpFrameNo, { getDstRect().x, getDstRect().y, 30, 20 }, { 0, 0 }, true, POWER_UPS, powerUpAnimationFilm);

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


