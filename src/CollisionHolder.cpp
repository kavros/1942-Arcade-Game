#include "Sprite.hpp"
#include "AnimatorHolder.h"
#include "Game.hpp"

void Sprite::fireHandler::operator()(Sprite* bullet,Sprite* arg) const{
    
    assert(bullet && arg);
    assert(bullet->isAlive() && arg->isAlive());
    
    if( !bullet->getVisibility() || !arg->getVisibility() )
        return;
    
    bullet->setVisibility(false);
    arg->setVisibility(false);
    
    Game::setScore(Game::getScore()+ 30);
    bullet->setState(IN_COLUSION);
    if (arg->getId().compare("SuperAce") == 0){
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
    }
    //bullet->destroySprite();
    //arg->destroySprite();
    
    AnimatorHolder::createExplosion( arg->getDstRect() );
}

Sprite::fireHandler* Sprite::fireHandler::Clone(void) const{
    return new Sprite::fireHandler();
}

Sprite::fireHandler::~fireHandler(){};

void Sprite::touchHandler::operator()(Sprite* aircraft,Sprite* arg) const{
    
    assert(aircraft && arg);
    assert(aircraft->isAlive() && arg->isAlive());
    
    if( !aircraft->getVisibility() || !arg->getVisibility())
        return;
    
    //SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
    //if( superAce == aircraft){

        aircraft->setVisibility(false);
        arg->setVisibility(false);
        
        if(arg->getId().compare("SuperAce") != 0){
           arg->setState(IN_COLUSION);
        }
        
        if (aircraft->getId().compare("SuperAce") != 0){
            aircraft->setState(IN_COLUSION);
        }
        if ((arg->getId().compare("SuperAce") == 0) || (aircraft->getId().compare("SuperAce") == 0)){
            SuperAce* sa = (SuperAce*) aircraft;
            if (arg->getId().compare("SuperAce") == 0){
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

        //aircraft->destroySprite();
        //arg->destroySprite();
    //}
    //else{
        //game over
    //}



    AnimatorHolder::createExplosion( aircraft->getDstRect() );
    
}

Sprite::touchHandler* Sprite::touchHandler::Clone(void) const{
    return new Sprite::touchHandler();
}

Sprite::touchHandler::~touchHandler(){};