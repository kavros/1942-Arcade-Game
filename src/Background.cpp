

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
    Background::_holder = this;
    Background::_holder->_terrainObjects = new SpriteList;
}

Background::~Background(){
}

void Background::InitBackground(){
    
    assert(Background::_holder);

    Background::_holder->initBackgroundObjects();
}

void Background::startBackgroundObjectAnimator(string id){
    MovingPathAnimator* backgroundAnimator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator(id);
    assert(backgroundAnimator);
    
    backgroundAnimator->start(Game::getGameTime());
}

void Background::startBackgroundObjectAnimators(){
    static int times = 0;
    assert(times==0);
    times++;
    
    MovingPathAnimator* backgroundAnimator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator("backgroundAnimator0");
    assert(backgroundAnimator);
    
    backgroundAnimator->start(Game::getGameTime());

    startBackgroundObjectAnimator("aircraftAnimator0");
    
   // startBackgroundObjectAnimator("spriteEurope0");
    // startBackgroundObjectAnimator("spriteLand0");


}
void Background::initBackgroundObjects(){

   // Background::_holder->addBackgroundObject("spriteEurope0");

    Background::_holder->addBackgroundObject("spriteAircraftCarrier1");

    //Background::_holder->addBackgroundObject("spriteLand0");
        
}

void Background::addBackgroundObject(string id){
    Sprite* s= SpritesHolder::getSprite(TERRAIN, id);
    assert(s);
    
    Background::_holder->_terrainObjects->push_back(s);
}

void Background::displayTerrain(SDL_Renderer* renderer){
    SpritesHolder::displaySprites(renderer, TERRAIN);
    
    if(Background::_holder->_terrainObjects->empty()){
        return;
    }
    
    for (std::list<Sprite*>::iterator it=Background::_holder->_terrainObjects->begin(); it != Background::_holder->_terrainObjects->end(); ++it){
        if((*it)->getVisibility() == true){
            (*it)->display(renderer);
        }
    }
}


Background::SpriteList Background::getVisibleObjects(){
    SpriteList* sl = new SpriteList;
    
    for (std::list<Sprite*>::iterator it=Background::_holder->_terrainObjects->begin(); it !=Background::_holder-> _terrainObjects->end(); ++it){
        if((*it)->getVisibility() == true){
            sl->push_back(*it);
        }
    }
    
    return *sl;
}


