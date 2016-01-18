#include "Sprite.hpp"
#include "AnimatorHolder.h"
#include "Game.hpp"

void Sprite::fireHandler::operator()(Sprite* bullet,Sprite* arg) const{
    if(!bullet || !arg)
        return;
    if( !bullet->getVisibility() || !arg->getVisibility())
        return;
    
    bullet->setVisibility(false);
    arg->setVisibility(false);
    bullet->Destroy();
    arg->Destroy();
    
    AnimatorHolder::createExplosion( arg->getDstRect() );
}

Sprite::fireHandler* Sprite::fireHandler::Clone(void) const{
    return new Sprite::fireHandler();
}

Sprite::fireHandler::~fireHandler(){};

void Sprite::touchHandler::operator()(Sprite* aircraft,Sprite* arg) const{
    if(!aircraft || !arg)
        return;
    if( !aircraft->getVisibility() || !arg->getVisibility())
        return;
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
    if( superAce == aircraft  &&  superAce->getSuperAceLives()>0 ){
        superAce->setSuperAceLives( superAce->getSuperAceLives() - 1 );
        Game::setState(SINGLEPLAYER_MENU);
    }
    else{
        aircraft->setVisibility(false);
        arg->setVisibility(false);
        
        aircraft->Destroy();
        arg->Destroy();
    }

    
    AnimatorHolder::createExplosion( aircraft->getDstRect() );
    
}

Sprite::touchHandler* Sprite::touchHandler::Clone(void) const{
    return new Sprite::touchHandler();
}

Sprite::touchHandler::~touchHandler(){};