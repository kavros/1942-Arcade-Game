

#include "Background.hpp"

Background *Background::_holder = 0;

void Background::filterMotion(int* dx, int* dy) const{

}

Background* Background::Get(){
    assert(_holder);
    return _holder;
}

Background* Background::Get(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm){
    _holder = new Background(id,_frameNo,_dstRect,_point,_isVisible,_type,_currFilm);
    assert(_holder);
    return _holder;
}

Background::Background(){
    assert(0);
}

Background::Background(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm):
Sprite(id,_frameNo,_dstRect,_point,_isVisible,_type,_currFilm){
    
    _terrainObjects = new SpriteList;
    
    MovingPathAnimation* backgroundAnimation = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("backgroundAnimation");
    assert(backgroundAnimation);
    
    MovingPathAnimator* backgroundAnimator = new MovingPathAnimator("BackgroundAnimator", this, backgroundAnimation);
    assert(backgroundAnimator);
    
    /*

    _dstRect.x = 0;
	_dstRect.y = -_currFilm->getFrameBox(0).h+WIN_HEIGHT;
    _dstRect.w = WIN_WIDTH;
    _dstRect.h =  _currFilm->getFrameBox(0).h;
    


    

 
     explosionAnimator->start(Game::getGameTime());
 
     //initBackgroundObjects();

    */

}

Background::~Background(){
}

void Background::initBackgroundObjects(){
   /*
    Sprite* initialAircraft = SpritesHolder::getSprite(TERRAIN, "spriteAircraftCarrier0");
    assert(initialAircraft);
    
    initialAircraft->setDstRectX(WIN_WIDTH/2-initialAircraft->getDstRect().w/2 + 13);
    initialAircraft->setDstRectY(WIN_HEIGHT-initialAircraft->getDstRect().h);
    */
    addBackgroundObject("spriteAircraftCarrier0");
    
    addBackgroundObject("spriteAircraftCarrier1");

    /*
    addBackgroundObject("spriteAircraftCarrier2");
    
    addBackgroundObject("spriteLand0");

    addBackgroundObject("spriteEurope0");
     */
}

void Background::addBackgroundObject(string id){
    Sprite* s= SpritesHolder::getSprite(TERRAIN, id);
    assert(s);
    _terrainObjects->push_back(s);
}

void Background::moveBackground(int dx, int dy){
    if(this->getVisibility() == true){
        if( this->getDstRect().y < 0 ){
            this->changeDstRectX(dx);
            this->changeDstRectY(dy);
        }
        else if( this->getDstRect().y >= 0 ){
            this->setDstRectY(-getDstRect().h+WIN_HEIGHT);
        }
            
        this->moveTerrainObjects(dx,dy);
    }

}

void Background::moveTerrainObjects(int dx, int dy){
    if(!_terrainObjects){
        return;
    }
    
    for (std::list<Sprite*>::iterator it=_terrainObjects->begin(); it != _terrainObjects->end(); ++it){
        if((*it)->getVisibility() == true){
            (*it)->changeDstRectX(dx);
            (*it)->changeDstRectY(dy);
        }
    }
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


