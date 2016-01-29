#include "SuperAce.h"

SuperAce::SuperAce(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm){

    _spriteId = id;
    _dstRect = dstRect;
    _dstRect.h = currFilm->getFrameBox(frameNo).h;
    _dstRect.w = currFilm->getFrameBox(frameNo).w;
    _point = point;
    setVisibility(isVisible);
    _type = type;
    _currFilm = currFilm;
    setFrame(frameNo);
    _superAceWidth= dstRect.w ;//_currFilm->getFrameBox(0).w;
    _superAceHeight= dstRect.h; //_currFilm->getFrameBox(0).h;
	_state = STARTING;
    _superAceLives = 1;
    AnimationFilm* animationBulletFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    
    _bulletDstRect.x=this->getDstRect().x + (this->getSuperAceWidth()/4);
    _bulletDstRect.y=this->getDstRect().y - this->getSuperAceHeigth();
    _bulletDstRect.w=animationBulletFilm->getFrameBox(2).w * Game::getSpriteSize();
    _bulletDstRect.h=animationBulletFilm->getFrameBox(2).h * Game::getSpriteSize();
    
    this->addCollisionHandler(Sprite::touchHandler());

    SpritesHolder::getSpritesHolder()->add(this);
    
    /*right side fighter*/
    /*unsigned rightSideFighterFrameNo = 0;
    SDL_Rect rightSideFighterDstRect = { static_cast<int>(_dstRect.x+_superAceWidth+8) , _dstRect.y , _dstRect.w , _dstRect.h};
    new SideFighter(this, RIGHT_FIGHTER, rightSideFighterFrameNo, rightSideFighterDstRect, point, isVisible, type, currFilm);
    assert(getAttached(RIGHT_FIGHTER));*/
    
    /*left side fighter*/
    /*unsigned leftSideFighterFrameNo = 0;
    SDL_Rect leftSideFighterDstRect = { _dstRect.x-_dstRect.w , _dstRect.y , _dstRect.w , _dstRect.h};
    new SideFighter(this, LEFT_FIGHTER, leftSideFighterFrameNo, leftSideFighterDstRect, point, isVisible, type, currFilm);
    assert(getAttached(LEFT_FIGHTER));*/


    
}

void SuperAce::render(SDL_Renderer * renderer){
	display(renderer);
};

unsigned SuperAce::getSuperAceWidth(){
    return _superAceWidth;
}

unsigned SuperAce::getSuperAceHeigth(){
    return _superAceHeight;
}

SDL_Rect SuperAce::getBulletDstRect(int frame){
    _bulletDstRect.x=(this->getDstRect().x + this->getDstRect().w/2 - _bulletDstRect.w/2);
    _bulletDstRect.y=this->getDstRect().y - this->getSuperAceHeigth()/3;
    return _bulletDstRect;
}

unsigned int SuperAce::getSuperAceLives(){
    return _superAceLives;
}

unsigned int SuperAce::getSuperAceLoops(){
    return _superAceLoops;
}

//set
void SuperAce::setSuperAceWidth(unsigned width){
    _superAceWidth = width;
}

void SuperAce::setSuperAceHeigth(unsigned height){
    _superAceHeight = height;
}

void SuperAce::setSuperAceLives(unsigned int superAceLives){
    _superAceLives = superAceLives;
}

void SuperAce::setSuperAceLoops(unsigned int superAceLoops){
    _superAceLoops = superAceLoops;
}

void SuperAce::fire(void){
    static string str = "spriteSuperAceFire";
    static int number = 0;
    string spriteSuperAceFireId = str + std::to_string (number);
    number++;
    
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    Sprite* bullet = new Sprite(spriteSuperAceFireId, 2, getBulletDstRect(2), {0,0}, true, SUPER_ACE, fireAnimationFilm);
    assert(bullet);
    
    //play sound for fire
    SoundHolder::playSound("gunshot");

    //fireAnimation
    Animation* fireAnimation = AnimationHolder::getAnimationHolder()->getAnimation("superAceFire");
    assert(fireAnimation);
    
    MovingAnimator* fireAnimator = new MovingAnimator("animatorFire", bullet, (MovingAnimation*)fireAnimation);
    
    AnimatorHolder::Register(fireAnimator);

    fireAnimator->start(Game::getGameTime());
    
    bullet->addCollisionHandler(Sprite::fireHandler());

    if (auto* left = getAttached(LEFT_FIGHTER))
        static_cast<SideFighter*>(left)->fire();
    if (auto* right = getAttached(RIGHT_FIGHTER))
        static_cast<SideFighter*>(right)->fire();
	
}

void SuperAce::doManeuever(void){
    if(getState() == MANEUVER){
        assert(0);
        return;
    }
    
    MovingPathAnimator* superAceAnimatorManeuever = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorManeuver");
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
    int loops = superAce->getSuperAceLoops();

    if (loops > 0){
        setState(MANEUVER);
        superAceAnimatorManeuever->start(Game::getGameTime());
        
        loops-=1;
        superAce->setSuperAceLoops(loops); 
        std::string _remainingLoops = "";
        for(int i = 0; i <  loops ; i++){
            _remainingLoops += "R";
        }
        cout<<_remainingLoops<<endl;
        
        SpriteStringHolder::getSpriteString("remainingLoops")->changeString(_remainingLoops, WIN_WIDTH - loops*12, WIN_HEIGHT - 15);
 
    }
    else if (loops == 0){
        
        //there are no loops
    }

}


void SuperAce::filterMotion(int* dx, int* dy) const {
    int old_x = _dstRect.x;
    int old_y = _dstRect.y;
    int new_x = _dstRect.x + * dx;
    int new_y = _dstRect.y + * dy;
        
    //adjust new_y if out of screen bounds
    int max_y = 0;
    if (new_y < max_y)
        new_y = max_y;
    
    int min_y =WIN_HEIGHT - _superAceHeight;// +100 - this->getDstRect().y;
    if (new_y > min_y)
        new_y = min_y;
    
    //adjust new_x if out of screen bounds
    int min_x = 0;
    if (new_x < min_x)
        new_x = min_x;
    
    int max_x =WIN_WIDTH - _superAceWidth;// +100 - this->getDstRect().y;
    if (new_x > max_x)
        new_x = max_x;
    
    //adjust new_x so that if there are any fighters
    // present they do not go beyond screen bounds
    
    auto* left = getAttached(LEFT_FIGHTER);
    auto* right = getAttached(RIGHT_FIGHTER);
    
    if(left){
        if(new_x < left->getDstRect().w){
            new_x = left->getDstRect().w;
        }
    }
    if(right){
        if(new_x > WIN_WIDTH - _superAceWidth - right->getDstRect().w){
            new_x = WIN_WIDTH - _superAceWidth - right->getDstRect().w;
        }
    }

    // now filter motion offset with actual motion possible
    *dx = new_x - old_x;
    *dy = new_y - old_y;
}

SideFighter::SideFighter(Sprite* ace, const std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm){
    ace->attach(this, id);
    
    _spriteId = id;
    _dstRect = dstRect;
    _dstRect.h = currFilm->getFrameBox(frameNo).h;
    _dstRect.w = currFilm->getFrameBox(frameNo).w;
    sideFighterWidth= dstRect.w ;//_currFilm->getFrameBox(0).w;
    sideFighterHeight= dstRect.h;
    _point = point;
    setVisibility(isVisible);
    _type = type;
    _currFilm = currFilm;
    setFrame(frameNo);
    _state = STARTING;
    
    AnimationFilm* animationBulletFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    
    sideFightertBulletDstRect.x=this->getDstRect().x + (this->getSideFighterWidth()/4);
    sideFightertBulletDstRect.y=this->getDstRect().y - this->getSideFighterHeight();
    sideFightertBulletDstRect.w=animationBulletFilm->getFrameBox(2).w * Game::getSpriteSize();
    sideFightertBulletDstRect.h=animationBulletFilm->getFrameBox(2).h * Game::getSpriteSize();
    
    this->addCollisionHandler(Sprite::touchHandler());
    
    SpritesHolder::getSpritesHolder()->add(this);
}

SideFighter::~SideFighter(){
    detach(this->getId(),false);
}

unsigned SideFighter::getSideFighterWidth(){
    return sideFighterWidth;
}

unsigned SideFighter::getSideFighterHeight(){
    return sideFighterHeight;
}

SDL_Rect SideFighter::getSideFightertBulletDstRect(){
    sideFightertBulletDstRect.x=(this->getDstRect().x + this->getDstRect().w/2 - sideFightertBulletDstRect.w/2);
    sideFightertBulletDstRect.y=this->getDstRect().y - this->getSideFighterHeight()/3;
    return sideFightertBulletDstRect;
}

void SideFighter::setSideFighterWidth(unsigned width){
    sideFighterWidth = width;
}

void SideFighter::setSideFighterHeight(unsigned height){
    sideFighterHeight = height;
}

void SideFighter::fire (void) {
    
    /* spawn bullet */
    static string str = "spriteSideSuperAceFire";
    static int number = 0;
    string spriteSideFighterFireId = str + std::to_string (number);
    number++;
    
    /*bullet test*/
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    Sprite* bullet = new Sprite(spriteSideFighterFireId, 2, getSideFightertBulletDstRect(), {0,0}, true, SUPER_ACE, fireAnimationFilm);
    assert(bullet);
    
    //play sound for fire
    SoundHolder::playSound("gunshot");
    
    //fireAnimation
    Animation* fireAnimation = AnimationHolder::getAnimationHolder()->getAnimation("superAceFire");
    assert(fireAnimation);
    
    MovingAnimator* fireAnimator = new MovingAnimator("animatorFire", bullet, (MovingAnimation*)fireAnimation);
    
    AnimatorHolder::Register(fireAnimator);
    
    fireAnimator->start(Game::getGameTime());
    
    bullet->addCollisionHandler(Sprite::fireHandler());
}

void SuperAce::addSideFighters(){
    /*right side fighter*/
    unsigned rightSideFighterFrameNo = 0;
    SDL_Rect rightSideFighterDstRect = { static_cast<int>(_dstRect.x+_superAceWidth) , _dstRect.y , _dstRect.w , _dstRect.h};
    new SideFighter(this, RIGHT_FIGHTER, rightSideFighterFrameNo, rightSideFighterDstRect, _point, _isVisible, _type, _currFilm);
    assert(getAttached(RIGHT_FIGHTER));
    
    /*left side fighter*/
    unsigned leftSideFighterFrameNo = 0;
    SDL_Rect leftSideFighterDstRect = { _dstRect.x-_dstRect.w , _dstRect.y , _dstRect.w , _dstRect.h};
    new SideFighter(this, LEFT_FIGHTER, leftSideFighterFrameNo, leftSideFighterDstRect, _point, _isVisible, _type, _currFilm);
    assert(getAttached(LEFT_FIGHTER));
}
