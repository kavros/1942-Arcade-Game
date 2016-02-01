

#include "Background.hpp"

Background *Background::_holder = 0;

void Background::filterMotion(int* dx, int* dy) const{

}
Background::Background():
Sprite("spriteEmpty_sea_background",0,{0,0,0,0},{0,0},true,TERRAIN,AnimationFilmHolder::Get()->GetFilm("empty_sea_background")){
    
    _dstRect.x = 0;
	_dstRect.y = -_currFilm->getFrameBox(0).h+WIN_HEIGHT;
    _dstRect.w = WIN_WIDTH;
    _dstRect.h =  _currFilm->getFrameBox(0).h;
    
    _terrainObjects = new SpriteList;

    initBackgroundObjects();
}

Background::~Background(){
}

void Background::initBackgroundObjects(){
   
    addBackgroundObject("spriteAircraftCarrier0");

    addBackgroundObject("spriteAircraftCarrier1");

    addBackgroundObject("spriteAircraftCarrier2");
    
    addBackgroundObject("spriteLand0");

    addBackgroundObject("spriteEurope");

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


