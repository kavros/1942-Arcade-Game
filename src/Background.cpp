

#include "Background.hpp"

Background *Background::_holder = 0;

void Background::filterMotion(int* dx, int* dy) const{

}
Background::Background(){
    
    _currFilm = AnimationFilmHolder::Get()->GetFilm("empty_sea_background");
    _spriteId = "spriteEmpty_sea_background";
    _terrainWidth = _currFilm->getFrameBox(0).w;
    _terrainHeight = _currFilm->getFrameBox(0).h;
    
    _isVisible = true;

    _dstRect.x = 0;
	_dstRect.y = -_terrainHeight+WIN_HEIGHT;
    _dstRect.w = WIN_WIDTH;
    _dstRect.h = _terrainHeight;

    _type = TERRAIN;
    
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
    
    
}

void Background::addBackgroundObject(string id){
    Sprite* s;
    s= SpritesHolder::getSpritesHolder()->getSprite(TERRAIN, id);
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
            this->setDstRectY(-_terrainHeight+WIN_HEIGHT);
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
            //cout<<(*it)->getId()<<endl;
            (*it)->changeDstRectX(dx);
            (*it)->changeDstRectY(dy);
        }
    }
}

void Background::displayTerrain(SDL_Renderer* renderer){
    SpritesHolder::getSpritesHolder()->displaySprites(renderer, TERRAIN);
    
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


