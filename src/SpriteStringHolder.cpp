#include "SpriteStringHolder.hpp"

SpriteStringHolder* SpriteStringHolder::holder = nullptr;

//constructor
SpriteStringHolder::SpriteStringHolder(){
    
}

//destructor
SpriteStringHolder::~SpriteStringHolder(){
    spriteStringMap.clear();
}

SpriteStringHolder* SpriteStringHolder::getSpriteStringHolder(){
    if(!holder){
        holder = new SpriteStringHolder();
    }
    return holder;
}

void SpriteStringHolder::addSpriteString(string id, SpriteString* spriteString){
    SpriteStringHolder::getSpriteStringHolder()->spriteStringMap[ id ] = spriteString;
}

SpriteString* SpriteStringHolder::getSpriteString(string id){
    return SpriteStringHolder::getSpriteStringHolder()->spriteStringMap[ id ];
}

void SpriteStringHolder::cleanup(){
    holder->~SpriteStringHolder();
    holder = NULL;
}