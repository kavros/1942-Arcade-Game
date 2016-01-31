  #include "Sprite.hpp"
#include "SpritesHolder.hpp"
#include "AnimatorHolder.h"

Sprite::Sprite(){
    assert(0);
    /*
    _frameNo=0;
    _dstRect={0,0,0,0};
    _point={0,0};
    setVisibility(true);
    _type=UNDEFINED;
    setState(FLYING);
    _currFilm=nullptr;
    _parent=nullptr;
    
     */
}

Sprite::Sprite(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm){
    assert( frameNo>=0 && currFilm!=NULL && type>=0 && type<SpriteType(SPRITE_TYPE_SIZE) && currFilm);

    _spriteId = id;
    _frameNo=frameNo;
    _dstRect = dstRect;
    _dstRect.h = currFilm->getFrameBox(frameNo).h * Game::getSpriteSize();
    _dstRect.w = currFilm->getFrameBox(frameNo).w * Game::getSpriteSize();
    _dstRect=dstRect;
    setVisibility(isVisible);
    _point=point;
    _type=type;
    _currFilm=currFilm;
    setState(FLYING);
    _parent=nullptr;

    SpritesHolder::add(this);

}

Sprite::~Sprite(){
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
    _dstRect.h = _currFilm->getFrameBox(_frameNo).h * Game::getSpriteSize();
    _dstRect.w = _currFilm->getFrameBox(_frameNo).w * Game::getSpriteSize();
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

SpriteState Sprite::getState(){
    return _state;
}

SpriteType Sprite::getType(){
    return _type;
}

void Sprite::move (int dx, int dy){
    filterMotion(&dx, &dy);
    //basic move logic
    _dstRect.x+=dx;
    _dstRect.y+=dy;
    moveAttached(dx, dy);
}

void Sprite::filterMotion(int* dx, int* dy) const {
    /* default is unfiltered motion */
};

void Sprite::moveAttached (int dx, int dy) {
    for (auto& i : _attached)
        i.second->move(dx,dy);
}

void Sprite::attach (Sprite* s, const std::string& name){
    _attached[name] = s;
    s->_parent = this;
    s->_name = name;
}

void Sprite::detach(const std::string& name, bool forDestroy){
    auto i  (_attached.find(name));
    assert(i != _attached.end());
    auto* s (i->second);
    s->_parent = nullptr;
    s->_name.clear();
    _attached.erase(i);
    if (forDestroy)
        s->destroySprite();
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
    assert(this->isAlive());
    assert(s->isAlive());
	
	
	if ((_state == MANEUVER) || s->_state == MANEUVER ){
		return;
	}

	//if sprites are not visible return
    if( !this->getVisibility() || !s->getVisibility() ){
        return;
    }
    //compare _dstRect with s->getDstRect()
	if (
		_dstRect.x < s->getDstRect().x + s->getDstRect().w &&
		_dstRect.x + _dstRect.w > s->getDstRect().x &&
		_dstRect.y < s->getDstRect().y + s->getDstRect().h &&
		_dstRect.h + _dstRect.y > s->getDstRect().y
		)
        notifyCollision(s);
}

//collision detection functions
void Sprite::notifyCollision(Sprite* arg){
    assert(arg);
    assert(this->isAlive());
    assert(arg->isAlive());

    Handlers::iterator i = _handlers.begin();
    Handlers::iterator i2;
    
    if( _spriteId.compare("SuperAce") == 0 ){
        if(_state==MANEUVER)
            return;
        
    }
    
    while(i!=_handlers.end()){
        i2=i;
        i2++;
        
        (**i)(this,arg);
            
        i=i2;
    }
}

void Sprite::addCollisionHandler(const CollisionHandler& h){
    _handlers.push_back(h.Clone());
    if( _type == SUPER_ACE){
        assert(this->getVisibility());

        SpriteList* aliens;
        
        aliens = SpritesHolder::getSprites(ALIEN_SHIP);
        
        if (aliens)
            for (SpriteList::iterator it=aliens->begin(); it != aliens->end(); ++it){
                if( ((Sprite*)*it)->isAlive() )
                    CollisionChecker::Register(this,*it);
            }
    }
    if( _type == ALIEN_SHIP || _type == POWER_UPS){
        SpriteList* superAce;
        
        superAce = SpritesHolder::getSpritesHolder()->getSprites(SUPER_ACE);
        
        if (superAce)
            for (SpriteList::iterator it=superAce->begin(); it != superAce->end(); ++it){
                if( ((Sprite*)*it)->isAlive() )
                    CollisionChecker::Register(this,*it);
            }
    }
}

void Sprite::clearHandlers(void){
    for(Handlers::const_iterator i = _handlers.begin(); i!=_handlers.end(); ++i ){
        delete *i;
    }
    
    _handlers.clear();

}

void Sprite::setState(SpriteState state){
	assert(FLYING <= state && state <= IN_COLUSION);
	_state = state;
}

void Sprite::destroySprite(void){
    assert(this->isAlive());
    //collisions
    CollisionChecker::CancelAll(this);
    clearHandlers();

    //SpritesHolder
    SpritesHolder::getSpritesHolder()->remove(this);
    
    LatelyDestroyable::destroy();
    
    // supports auto detach policy
    if (_parent)	// is attached
        _parent->detach(_name, false);
}

Sprite* Sprite::getParent(){
    return _parent;
}
