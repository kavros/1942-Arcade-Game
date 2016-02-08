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
#include "PowerUp.hpp"

enum EnemyFighterType{
    RED_PLANE = 0,
    MIN_GREEN_JET = 1,
    MIN_GREY_JET = 2,
    MIN_GREEN_ONE_ENG = 3 ,
    MIN_GREY_ONE_ENG = 4,
    MIN_GREEN_DOUBLE_ENG = 5 ,
    MIN_GREY_DOUBLE_ENG = 6,
    MED_GREEN_ONE_ENG = 7,
    MED_GREEN_DOUBLE_ENG = 8,
    MED_GREEN_TRIPLE_ENG = 9,
    MED_GREY_ONE_ENG = 10,
    MED_GREY_DOUBLE_ENG = 11,
    MED_GREY_TRIPLE_ENG = 12,
    BIG_GREEN = 13,
    BIG_GREY = 14,
    BULLET = 15,
    DEATH_STAR = 16
};
class EnemyFighter:public Sprite{
    
private:
    enum EnemyFighterType _enemyType;
    bool enemyFireEnable;
    unsigned remainingBullets;
    unsigned bulletFrame;
    SDL_Rect _enemyBulletDstRect;
    AnimationFilm* animationEnemyBulletFilm;
    unsigned enemyFighterLifes;
public:
    
    //constructor
    EnemyFighter();
    EnemyFighter(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm,enum EnemyFighterType e,unsigned remainingBullets);
    
    //get
    SDL_Rect getEnemyBulletDstRect();
    enum EnemyFighterType getEnemyFighterType();
    bool getEnemyFireEnable();
    AnimationFilm* getAnimationEnemyBulletFilm();
    unsigned getRemainingBullets();
    unsigned getBulletFrame();
    unsigned getEnemyFighterLifes();
    
    //set
    void setFrame(unsigned i) override;
    void setEnemyFireEnable(bool fire);
    void setAnimationEnemyBulletFilm(AnimationFilm* film);
    void setEnemyFighterType(enum EnemyFighterType type);
    void setRemainingBullets(unsigned bullets);
    void setBulletFrame(unsigned frame);
    void setEnemyFighterLifes(unsigned lifes);
    
    //functionallity
    void fire();
    void fireSideRightBullet();
    void fireSideLeftBullet();
    void fireSideRightRightBullet();
    void fireSideLeftLeftBullet();
    void fireStraightBullet();
	void createPowerUp();
    void updateScore();
};

#endif