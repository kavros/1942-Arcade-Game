#include "Sprite.hpp"
#include "SpritesHolder.hpp"

void Sprite::moveAttached (int dx, int dy) {
    for (auto& i : _attached)
        i.second->move(dx,dy);
}

Sprite::Sprite(){
    _frameNo=0;
    _dstRect={0,0,0,0};
    _point={0,0};
    _isVisible=false;
    _type=UNDEFINED;
    _state=FLYING;
    _currFilm=nullptr;
    alive=true;
    //assert(0);
}

Sprite::Sprite(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm){
    assert(frameNo>=0 && currFilm!=NULL && type>=0 && type<SPRITE_TYPE_SIZE);
    //cout<<"TYPE "<<type;
    _spriteId = id;
    _frameNo=frameNo;
    _dstRect=dstRect;
    _point=point;
    _isVisible=isVisible;
    _type=type;
    _currFilm=currFilm;
    _state=FLYING;
    alive=true;
    
    registerCollision();
}

Sprite::Sprite(std::string id, SDL_Rect dstRect,bool isVisible,SpriteType type,AnimationFilm* currFilm){
    assert(currFilm!=NULL && type>=0 && type<SPRITE_TYPE_SIZE);
    _spriteId = id;
    cout<<"TYPE "<<type;
    _frameNo=0;
    _dstRect=dstRect;
    _point={0,0};
    _isVisible=isVisible;
    _type=type;
    _currFilm=currFilm;
    _state=FLYING;
    alive=true;
    
    registerCollision();

}

Sprite::~Sprite(){
    clearHandlers();
}

void Sprite::setId(std::string id){
    _spriteId = id;
}
void Sprite::setCurrFilm(AnimationFilm* currFilm){
    _currFilm = currFilm;
}
AnimationFilm* Sprite::getCurrFilm(void) const{
    return  _currFilm;
}

void Sprite::setFrame(unsigned i){
	assert(0 < i < _currFilm->getTotalFrames());
	_frameNo = i;
}

unsigned Sprite::getFrame(void) const {
    return _frameNo;
}

void Sprite::setDstRect(SDL_Rect dstRect){
    _dstRect=dstRect;
}

void Sprite::setDstRectX(int x){
    _dstRect.x=x;
}
void Sprite::setDstRectY(int y){
    _dstRect.y=y;

}

std::string Sprite::getId(void) const{
    return _spriteId;
}

SDL_Rect Sprite::getDstRect(void) const{
    return _dstRect;
}

SpriteType Sprite::getType(){
    return _type;
}

void Sprite::changeDstRectX(int dx){
    _dstRect.x+=dx;
}
void Sprite::changeDstRectY(int dy){
    _dstRect.y+=dy;
}

void Sprite::setVisibility (bool v) {
    _isVisible = v;
}

bool Sprite::getVisibility (void) const{
    return _isVisible;
}

void Sprite::move (int dx, int dy){
    filterMotion(&dx, &dy);
    //basic move logic
    _dstRect.x+=dx;
    _dstRect.y+=dy;
    //moveAttached(dx, dy);
}

void Sprite::attach (Sprite* s, const std::string& name){
    _attached[name] = s;
    s->_parent = this;
    s->_name = name;
}

void Sprite::detach(const std::string& name, bool destroy){
    auto i  (_attached.find(name));
    assert(i != _attached.end());
    auto* s (i->second);
    s->_parent = nullptr;
    s->_name.clear();
    _attached.erase(i);
    if (destroy)
        s->Destroy();
}

Sprite* Sprite::getAttached(const std::string& name) const{
    auto i  (_attached.find(name));
    return i != _attached.end() ? i->second : nullptr;
}

void Sprite::display(SDL_Renderer* renderer) {
    _currFilm->displayFrame(renderer,_point,_frameNo,_dstRect);
}

bool Sprite::isOutOfWindow(){
    int x = getDstRect().x;
    int y = getDstRect().y;
    int w = getDstRect().w;
    int h = getDstRect().h;
    int extra_dst = 5;
    
    if( x > -w - extra_dst && y > -h - extra_dst && x < WIN_WIDTH + extra_dst && y < WIN_HEIGHT + extra_dst ){
        return false;
    }

    return true;
}

// TODO :: CollisionCheck body
void Sprite::collisionCheck(Sprite* s){
    //compare _dstRect with s->getDstRect()
    if(
        _dstRect.x < s->getDstRect().x + s->getDstRect().w &&
        _dstRect.x + _dstRect.w > s->getDstRect().x &&
        _dstRect.y < s->getDstRect().y + s->getDstRect().h &&
        _dstRect.h + _dstRect.y > s->getDstRect().y
       )
        notifyCollision(s);
}

/*
 typedef enum SpriteType {
 MAIN_MENU_SINGLEPLAYER = 0,
 MAIN_MENU_MULTIPLAYER,
 TERRAIN,
 SUPER_ACE,
 ALIEN_SHIP,
 BIG_ALIEN_SHIP,
 POWER_UPS,
 GAME_INFO,
 UNDEFINED
 }SpriteType;
 
 CollisionChecker::Register(superAce,fireSprite);
 */

void Sprite::registerCollision(){
    
    if( _type >=SUPER_ACE && _type <=BIG_ALIEN_SHIP ){
        
        SpriteType st = SUPER_ACE;
        while(st >=SUPER_ACE && st <=BIG_ALIEN_SHIP){
            if(st != _type){
                
                SpriteList* sl = SpritesHolder::getSpritesHolder()->getSprites(st);
                
                if(sl)
                    for (SpriteList::iterator it=sl->begin(); it != sl->end(); ++it){
                    
                        CollisionChecker::Register(this,*it);
                    }
                
            }
            
            st = SpriteType(st+1);
        }
    }
}





