#include "Sprite.hpp"
#include "AnimatorHolder.h"
#include "Game.hpp"
#include "PowerUp.hpp"

void Sprite::fireHandler::operator()(Sprite* bullet,Sprite* arg) const{
    
    assert(bullet && arg);
    assert(bullet->isAlive() && arg->isAlive());
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");

	if (arg == superAce){
		//cout << "FIRE HANDLER DEALING WITH SUPERACE" << endl;
		if (arg->_state == MANEUVER){
			//cout << " AND Super Ace state is MANEUVER" << endl;
			return;
		}
	}
	if( !bullet->getVisibility() || !arg->getVisibility() )
        return;
    
    bullet->setState(IN_COLUSION);
    arg->setVisibility(false);
    bullet->setVisibility(false);
    Game::setScore(Game::getScore()+ 30);
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
    }else{
        arg->setState(IN_COLUSION);
        if(arg->getType() == ALIEN_SHIP){
            if( ((EnemyFighter*)arg)->getEnemyFighterType() == RED_PLANE ){
				((EnemyFighter*)arg)->createPowerUp();
            }
        }
    }
    
    AnimatorHolder::createExplosion( arg->getDstRect() );
}

Sprite::fireHandler* Sprite::fireHandler::Clone(void) const{
    return new Sprite::fireHandler();
}

Sprite::fireHandler::~fireHandler(){};

void Sprite::touchHandler::operator()(Sprite* aircraft,Sprite* arg) const{
    
    assert(aircraft && arg);
    assert(aircraft->isAlive() && arg->isAlive());
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");

    if( !aircraft->getVisibility() || !arg->getVisibility())
        return;
    
    //SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
    //if( superAce == aircraft){

        aircraft->setVisibility(false);
        arg->setVisibility(false);
        
        if(arg != superAce){
           arg->setState(IN_COLUSION);
        }
        
        if (aircraft != superAce){
            aircraft->setState(IN_COLUSION);
        }
        if ( arg == superAce || aircraft != superAce ){
            SuperAce* sa = (SuperAce*) aircraft;
            if ( arg == superAce ){
                sa = (SuperAce*) arg;
            }
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
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");
    Sprite* rightFighter = superAce->getAttached(RIGHT_FIGHTER);
    Sprite* leftFighter = superAce->getAttached(LEFT_FIGHTER);

    if( superAce == arg || rightFighter == arg || leftFighter == arg ){
        powerUp->setVisibility(false);
        ((PowerUp*)powerUp)->activatePowerUp(arg);
        powerUp->setState(IN_COLUSION);
    }

}

Sprite::touchPowerUpHandler* Sprite::touchPowerUpHandler::Clone(void) const{
    return new Sprite::touchPowerUpHandler();
}

Sprite::touchPowerUpHandler::~touchPowerUpHandler(){}