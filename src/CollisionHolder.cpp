#include "Sprite.hpp"
#include "AnimatorHolder.h"

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
    
    aircraft->setVisibility(false);
    arg->setVisibility(false);
    
    aircraft->Destroy();
    arg->Destroy();
    
    AnimatorHolder::createExplosion( aircraft->getDstRect() );
    
}

Sprite::touchHandler* Sprite::touchHandler::Clone(void) const{
    return new Sprite::touchHandler();
}

Sprite::touchHandler::~touchHandler(){};