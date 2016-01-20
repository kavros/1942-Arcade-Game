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
    bullet->destroySprite();
    arg->destroySprite();
    
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
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
    if( superAce == aircraft/*  &&  superAce->getSuperAceLives()>0 */){
        //superAce->setSuperAceLives( superAce->getSuperAceLives() - 1 );
        //assert(0);
        //end of life
        //Game::setState(SINGLEPLAYER_MENU);

        aircraft->setVisibility(false);
        arg->setVisibility(false);
        aircraft->destroySprite();
        arg->destroySprite();
    }

    AnimatorHolder::createExplosion( aircraft->getDstRect() );
    
}

Sprite::touchHandler* Sprite::touchHandler::Clone(void) const{
    return new Sprite::touchHandler();
}

Sprite::touchHandler::~touchHandler(){};