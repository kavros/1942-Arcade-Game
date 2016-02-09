#include "Sprite.hpp"
#include "AnimatorHolder.h"
#include "Game.hpp"
#include "PowerUp.hpp"

void Sprite::fireHandler::operator()(Sprite* bullet,Sprite* arg) const{
    
    assert(bullet && arg);
    assert(bullet->isAlive() && arg->isAlive());
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    assert(superAce);
    
	if( !bullet->getVisibility() || !arg->getVisibility() )
        return;
    
    if (arg == superAce && arg->getState() == MANEUVER){
        return;
    }

	
    bullet->setState(IN_COLUSION);
    arg->setVisibility(false);
    bullet->setVisibility(false);
    //Game::setScore(Game::getScore()+ 30);
    if (arg == superAce){
        SuperAce* sa = (SuperAce*) arg;
        if(sa->getSuperAceLives() > 1){
            sa->setSuperAceLives(sa->getSuperAceLives() - 1);
            std::string _remainingLives = "";
            for(int i = 0; i < sa->getSuperAceLives() ; i++){
                _remainingLives += "L";
            }
            SpriteStringHolder::getSpriteString("remainingLives")->changeString(_remainingLives, +5/*WIN_WIDTH - loops*12 -5*/, WIN_HEIGHT -15);
        }else{
            sa->setState(IN_COLUSION);
        }
    }else if( arg->getType() == ALIEN_SHIP ){
        
        EnemyFighter* enemyFighter = ( EnemyFighter* )arg;
        
        if(enemyFighter->getEnemyFighterLifes() == 1){
            
            enemyFighter->setState(IN_COLUSION);
            Game::setToDeadEnemiesOneMore();

            if(enemyFighter->getEnemyFighterType() == RED_PLANE && SpritesHolder::uniqueAliveFromTeam(enemyFighter) ){
                enemyFighter->createPowerUp();
            }
            
        }
        enemyFighter->setEnemyFighterLifes( enemyFighter->getEnemyFighterLifes() -1 );
        enemyFighter->updateScore();
    }
    else if( arg->getType() == SUPER_ACE ){
        Sprite* rightFighter = superAce->getAttached(RIGHT_FIGHTER);
        Sprite* leftFighter = superAce->getAttached(LEFT_FIGHTER);
        if( rightFighter == arg || leftFighter == arg ){
            arg->setState(IN_COLUSION);
        }
        else{
            assert(0);
        }
    }
    else{
        assert(0);
    }
    
    AnimatorHolder::createExplosion( arg->getDstRect() );
}

void EnemyFighter::updateScore(){
    EnemyFighterType t = this->getEnemyFighterType();
    int i =0;
    switch (t){
        case EnemyFighterType(0): i = 30; break;
        case EnemyFighterType(MIN_GREEN_JET): i = 30; break;
        case EnemyFighterType(MIN_GREY_JET): i = 30; break;
        case EnemyFighterType(MIN_GREEN_ONE_ENG): i = 30; break;
        case EnemyFighterType(MIN_GREY_ONE_ENG): i = 50; break;
        case EnemyFighterType(MIN_GREEN_DOUBLE_ENG): i = 70; break;
        case EnemyFighterType(MIN_GREY_DOUBLE_ENG): i = 70; break;
        case EnemyFighterType(MED_GREEN_ONE_ENG): {
            if(this->getState() == IN_COLUSION){
                i = 1000;
                AnimatorHolder::createUpdateScoreAnimator(this->getDstRect(),1000);
            }
            else
                i = 100;
            break;
        }
        case EnemyFighterType(MED_GREEN_DOUBLE_ENG):{
            if(this->getState() == IN_COLUSION){
                i = 1000;
                AnimatorHolder::createUpdateScoreAnimator(this->getDstRect(),1000);
            }
            else
                i = 100;
            break;
        }
        case EnemyFighterType(MED_GREEN_TRIPLE_ENG):{
            if(this->getState() == IN_COLUSION){
                i = 1000;
                AnimatorHolder::createUpdateScoreAnimator(this->getDstRect(),1000);
            }
            else
                i = 100;
            break;
        }
        case EnemyFighterType(MED_GREY_ONE_ENG): {
            if(this->getState() == IN_COLUSION){
                i = 1500;
                AnimatorHolder::createUpdateScoreAnimator(this->getDstRect(),1500);
            }
            else
                i = 100;
            break;
        }
        case EnemyFighterType(MED_GREY_DOUBLE_ENG): {
            if(this->getState() == IN_COLUSION){
                i = 1500;
                AnimatorHolder::createUpdateScoreAnimator(this->getDstRect(),1500);
            }
            else
                i = 100;
            break;
        }
        case EnemyFighterType(MED_GREY_TRIPLE_ENG): {
            if(this->getState() == IN_COLUSION){
                i = 1500;
                AnimatorHolder::createUpdateScoreAnimator(this->getDstRect(),1500);
            }
            else
                i = 100;
            break;
        }
        case EnemyFighterType(BIG_GREEN): {
            if(this->getState() == IN_COLUSION){
                i = 2000;
                AnimatorHolder::createUpdateScoreAnimator(this->getDstRect(),2000);
            }
            else
                i = 100;
            break;
        }
        case EnemyFighterType(BIG_GREY): {
            if(this->getState() == IN_COLUSION){
                i = 2000;
                AnimatorHolder::createUpdateScoreAnimator(this->getDstRect(),2000);
            }
            else
                i = 100;
            break;
        }
        case EnemyFighterType(DEATH_STAR): {
            if(this->getState() == IN_COLUSION){
                i = 1000;
                AnimatorHolder::createUpdateScoreAnimator(this->getDstRect(),1000);
            }
            else
                i = 100;
            break;
        }
        case EnemyFighterType(BULLET): {
            break;
        }
        default: assert(0);
    }
    Game::setScore(Game::getScore()+ i);
}

Sprite::fireHandler* Sprite::fireHandler::Clone(void) const{
    return new Sprite::fireHandler();
}

Sprite::fireHandler::~fireHandler(){};

void Sprite::touchHandler::operator()(Sprite* aircraft,Sprite* arg) const{
    
    assert(aircraft && arg);
    assert(aircraft->isAlive() && arg->isAlive());
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");

    if( !aircraft->getVisibility() || !arg->getVisibility())
        return;


    aircraft->setVisibility(false);
    arg->setVisibility(false);
    
    if(arg != superAce){
        arg->setState(IN_COLUSION);
        
        if(arg->getType() == ALIEN_SHIP){
            EnemyFighter* enemyFighter = ( EnemyFighter* )arg;

            if(enemyFighter->getEnemyFighterLifes() == 1){
                enemyFighter->setState(IN_COLUSION);
                Game::setToDeadEnemiesOneMore();
            }
            enemyFighter->setEnemyFighterLifes( enemyFighter->getEnemyFighterLifes() -1 );

        }

    }
    
    if (aircraft != superAce){
        aircraft->setState(IN_COLUSION);
        
        if(aircraft->getType() == ALIEN_SHIP){
            EnemyFighter* enemyFighter = ( EnemyFighter* )aircraft;
            if(enemyFighter->getEnemyFighterLifes() == 1){
                enemyFighter->setState(IN_COLUSION);
                Game::setToDeadEnemiesOneMore();
            }
            enemyFighter->setEnemyFighterLifes( enemyFighter->getEnemyFighterLifes() -1 );
        }
        
    }
    if ( arg == superAce || aircraft == superAce ){

        if(superAce->getSuperAceLives() > 1){
            superAce->setSuperAceLives(superAce->getSuperAceLives() - 1);
            std::string _remainingLives = "";
            for(int i = 0; i < superAce->getSuperAceLives() ; i++){
                _remainingLives += "L";
            }
            cout<<_remainingLives<<"\n";
            SpriteStringHolder::getSpriteString("remainingLives")->changeString(_remainingLives, +5/*WIN_WIDTH - loops*12 -5*/, WIN_HEIGHT -15);
        }else{
            superAce->setState(IN_COLUSION);
        }
    }

    AnimatorHolder::createExplosion( aircraft->getDstRect() );
    
}

Sprite::touchHandler* Sprite::touchHandler::Clone(void) const{
    return new Sprite::touchHandler();
}

Sprite::touchHandler::~touchHandler(){};

void Sprite::touchPowerUpHandler::operator()(Sprite* powerUp,Sprite* arg) const{
    
    assert(powerUp && arg);
    assert(powerUp->isAlive() && arg->isAlive());

    if( !powerUp->getVisibility() || !arg->getVisibility())
        return;
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    Sprite* rightFighter = superAce->getAttached(RIGHT_FIGHTER);
    Sprite* leftFighter = superAce->getAttached(LEFT_FIGHTER);

    if( superAce == arg || rightFighter == arg || leftFighter == arg ){
		SoundHolder::playSound("PowerUp");
        powerUp->setVisibility(false);
        ((PowerUp*)powerUp)->activatePowerUp(arg);
        powerUp->setState(IN_COLUSION);
    }

}

Sprite::touchPowerUpHandler* Sprite::touchPowerUpHandler::Clone(void) const{
    return new Sprite::touchPowerUpHandler();
}

Sprite::touchPowerUpHandler::~touchPowerUpHandler(){}