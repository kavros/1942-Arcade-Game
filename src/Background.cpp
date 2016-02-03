

#include "Background.hpp"

Background *Background::_holder = 0;

void Background::filterMotion(int* dx, int* dy) const{

}

Background* Background::Get(){
    assert(Background::_holder);
    return Background::_holder;
}

Background* Background::Get(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm){
    Background::_holder = new Background(id,_frameNo,_dstRect,_point,_isVisible,_type,_currFilm);
    assert(Background::_holder);
    return Background::_holder;
}

Background::Background(){
    assert(0);
}

Background::Background(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm):
Sprite(id,_frameNo,_dstRect,_point,_isVisible,_type,_currFilm){
    _terrainObjects = new SpriteList;
}

Background::~Background(){
}

void Background::InitBackground(){
    
    assert(Background::_holder);
    /*
    MovingPathAnimation* backgroundAnimation = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("backgroundAnimation");
    assert(backgroundAnimation);
    */
    MovingPathAnimator* backgroundAnimator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator("backgroundAnimator0");
    assert(backgroundAnimator);
    
    backgroundAnimator->start(Game::getGameTime());

    Background::_holder->initBackgroundObjects();
}

void Background::startBackgroundObjectAnimator(string id){
    MovingPathAnimator* backgroundAnimator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator(id);
    assert(backgroundAnimator);
    
    backgroundAnimator->start(Game::getGameTime());
}

void Background::initBackgroundObjects(){
    //aircraftAnimator

    Sprite* initialAircraft = SpritesHolder::getSprite(TERRAIN, "spriteAircraftCarrier0");
    assert(initialAircraft);
    
    initialAircraft->setDstRectX(WIN_WIDTH/2-initialAircraft->getDstRect().w/2 + 13);
    initialAircraft->setDstRectY(WIN_HEIGHT-initialAircraft->getDstRect().h);
    
    Sprite* finishAircraft = SpritesHolder::getSprite(TERRAIN, "spriteAircraftCarrier1");
    assert(finishAircraft);
    
    finishAircraft->setDstRectX(WIN_WIDTH/2-initialAircraft->getDstRect().w/2 + 13);
    finishAircraft->setDstRectY(-finishAircraft->getDstRect().h);
    
    addBackgroundObject("spriteAircraftCarrier0");
    startBackgroundObjectAnimator("aircraftAnimator0");

    addBackgroundObject("spriteAircraftCarrier1");

    addBackgroundObject("spriteLand0");
    startBackgroundObjectAnimator("spriteLandAnimator0");
    
    addBackgroundObject("spriteEurope0");
    startBackgroundObjectAnimator("spriteEuropeAnimator0");
}

void Background::addBackgroundObject(string id){
    Sprite* s= SpritesHolder::getSprite(TERRAIN, id);
    assert(s);
    
    _terrainObjects->push_back(s);
}

void Background::displayTerrain(SDL_Renderer* renderer){
    SpritesHolder::displaySprites(renderer, TERRAIN);
    
    if(_terrainObjects->empty()){
        return;
    }
    
    for (std::list<Sprite*>::iterator it=_terrainObjects->begin(); it != _terrainObjects->end(); ++it){
        if((*it)->getVisibility() == true){
            (*it)->display(renderer);
        }
    }
}


Background::SpriteList Background::getVisibleObjects(){
    SpriteList* sl = new SpriteList;
    
    for (std::list<Sprite*>::iterator it=_terrainObjects->begin(); it != _terrainObjects->end(); ++it){
        if((*it)->getVisibility() == true){
            sl->push_back(*it);
        }
    }
    
    return *sl;
}


