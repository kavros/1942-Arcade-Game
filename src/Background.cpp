#include "../includes/Background.hpp"

Background* Background::_holder = nullptr;

void Background::filterMotion(int* dx, int* dy) const{
}

Background* Background::Get(){
    assert(_holder);
    return _holder;
}

Background::Background(){
    assert(0);
}

Background::Background(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm):
Sprite(id,_frameNo,_dstRect,_point,_isVisible,_type,_currFilm){
    static int times = 0;
    assert(times==0);
    times++;
    
    Background::_holder = this;
    this->setUndefeatable(true);
    this->_terrainObjects = new SpriteList;
}

Background::~Background(){
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

    startBackgroundObjectAnimator("backgroundAnimator0");
    startBackgroundObjectAnimator("aircraftAnimator0");
    startBackgroundObjectAnimator("spriteEuropeAnimator0");
    startBackgroundObjectAnimator("spriteAfricaAnimator0");

    //startBackgroundObjectAnimator("spriteLandAnimator0");

    
}
void Background::initBackgroundObjects(){
    static int times = 0;
    assert(times==0);
    times++;

    Background* b = Background::Get();
    assert(b);
    
    b->addBackgroundObject("spriteAircraftCarrier0");

    b->addBackgroundObject("spriteAircraftCarrier1");

    b->addBackgroundObject("spriteEurope0");

    b->addBackgroundObject("spriteAfrica0");

    //b->addBackgroundObject("spriteLand0");
  
}

void Background::addBackgroundObject(string id){
    Sprite* s= SpritesHolder::getSprite(TERRAIN, id);
    assert(s);
    this->_terrainObjects->push_back(s);
    assert(!this->_terrainObjects->empty());
}

void Background::displayTerrain(SDL_Renderer* renderer){

    Background* b = Background::Get();
    assert(b);
    b->display(renderer);
    
    if(b->_terrainObjects->empty()){
        return;
    }
    
    for (std::list<Sprite*>::iterator it=b->_terrainObjects->begin(); it != b->_terrainObjects->end(); ++it){
        if((*it)->getVisibility() == true){
            (*it)->display(renderer);
        }
    }
     
}

