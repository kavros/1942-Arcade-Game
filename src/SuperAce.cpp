#include "SuperAce.h"

SuperAce::SuperAce(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm):
Sprite(id,frameNo,dstRect,point,isVisible,type,currFilm){

    _superAceLives = 1;

    setBulletAnimationFilm(AnimationFilmHolder::Get()->GetFilm("bullets"));
    
    bulletFrame = 2;
    _bulletDstRect.w=bulletAnimationFilm->getFrameBox(bulletFrame).w * Game::getSpriteSize();
    _bulletDstRect.h=bulletAnimationFilm->getFrameBox(bulletFrame).h * Game::getSpriteSize();
    _bulletDstRect.x=this->getDstRect().x + this->getDstRect().w/2 - _bulletDstRect.w/2;
    _bulletDstRect.y=this->getDstRect().y;

    this->addCollisionHandler(Sprite::touchHandler());

}

void SuperAce::render(SDL_Renderer * renderer){
	display(renderer);
};

SDL_Rect SuperAce::getBulletDstRect(){
    _bulletDstRect.x=this->getDstRect().x + this->getDstRect().w/2 - _bulletDstRect.w/2;
    _bulletDstRect.y=this->getDstRect().y ;
    
    return _bulletDstRect;
}

unsigned int SuperAce::getSuperAceLives(){
    return _superAceLives;
}

unsigned int SuperAce::getSuperAceLoops(){
    return _superAceLoops;
}

unsigned int SuperAce::getBulletFrame(){
    return bulletFrame;
}

//set
void SuperAce::setSuperAceLives(unsigned int superAceLives){
    this->_superAceLives = superAceLives;
}

void SuperAce::setSuperAceLoops(unsigned int superAceLoops){
    _superAceLoops = superAceLoops;
}

void SuperAce::setBulletFrame(unsigned int _bulletFrame){
    AnimationFilm* animationBulletFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(animationBulletFilm);
    
    bulletFrame = _bulletFrame;
    
    getBulletDstRect();
}

void SuperAce::setBulletDstRect(SDL_Rect bulletDstRect){
    this->_bulletDstRect = bulletDstRect;
}

void SuperAce::setBulletAnimationFilm(AnimationFilm* anim){
    bulletAnimationFilm = anim;
    assert(bulletAnimationFilm);
}

void SuperAce::fire(void){

    static int number = 0;
    string spriteSuperAceFireId = "spriteSuperAceFire" + std::to_string (number);
    string animatorSuperAceFireId = "animatorSuperAceFire" + std::to_string (number);

    number++;
    
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    Sprite* bullet = new Sprite(spriteSuperAceFireId, bulletFrame, getBulletDstRect(), {0,0}, true, SUPER_ACE, fireAnimationFilm);
    assert(bullet);
    
    //play sound for fire
    SoundHolder::playSound("gunshot");

    //fireAnimation
    Animation* fireAnimation = AnimationHolder::getAnimationHolder()->getAnimation("superAceFire");
    assert(fireAnimation);
    
    MovingAnimator* fireAnimator = new MovingAnimator(animatorSuperAceFireId, bullet, (MovingAnimation*)fireAnimation);
    assert(fireAnimator);
    
    fireAnimator->start(Game::getGameTime());
    
    bullet->addCollisionHandler(Sprite::fireHandler());

    if (auto* left = getAttached(LEFT_FIGHTER))
        static_cast<SideFighter*>(left)->fire();
    if (auto* right = getAttached(RIGHT_FIGHTER))
        static_cast<SideFighter*>(right)->fire();
	
}

void SuperAce::doManeuever(void){
    if(getState() == MANEUVER){       
        return;
    }

    MovingPathAnimator* superAceAnimatorManeuever = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorManeuver");
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");
    int loops = superAce->getSuperAceLoops();
	
    if (loops > 0){
        setState(MANEUVER);
		cout << "SuperAce state is now Maneuver" << endl;
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
    
    int min_y =WIN_HEIGHT - getDstRect().h;// +100 - this->getDstRect().y;
    if (new_y > min_y)
        new_y = min_y;
    
    //adjust new_x if out of screen bounds
    int min_x = 0;
    if (new_x < min_x)
        new_x = min_x;
    
    int max_x =WIN_WIDTH - getDstRect().w;// +100 - this->getDstRect().y;
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
        if(new_x > WIN_WIDTH - getDstRect().w - right->getDstRect().w){
            new_x = WIN_WIDTH - getDstRect().w - right->getDstRect().w;
        }
    }

    // now filter motion offset with actual motion possible
    *dx = new_x - old_x;
    *dy = new_y - old_y;
}

SideFighter::SideFighter(Sprite* ace, const std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm):
Sprite(id,frameNo,dstRect,point,isVisible,type,currFilm){
    
    assert(!isOutOfWindow());
    
    ace->attach(this, id);

    bulletFrame = 1;

    bulletAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(bulletAnimationFilm);
    
    sideFightertBulletDstRect.w=bulletAnimationFilm->getFrameBox(bulletFrame).w * Game::getSpriteSize() * 1.2;
    sideFightertBulletDstRect.h=bulletAnimationFilm->getFrameBox(bulletFrame).h * Game::getSpriteSize() * 1.2;
    sideFightertBulletDstRect.x=this->getDstRect().x + getDstRect().w/2 - sideFightertBulletDstRect.w/2;
    sideFightertBulletDstRect.y=this->getDstRect().y;

    this->addCollisionHandler(Sprite::touchHandler());
}

SideFighter::~SideFighter(){
    detach(this->getId(),false);
}

SDL_Rect SideFighter::getSideFightertBulletDstRect(){
    sideFightertBulletDstRect.x=this->getDstRect().x + getDstRect().w/2 - sideFightertBulletDstRect.w/2;
    sideFightertBulletDstRect.y=this->getDstRect().y;
    return sideFightertBulletDstRect;
}

void SideFighter::fire (void) {
    
    /* spawn bullet */
    static int number = 0;
    string spriteSideFighterFireId = "spriteSideSuperAceFire" + std::to_string (number);
    string animatorSideFighterFireId = "animatorSideSuperAceFire" + std::to_string (number);
    
    number++;
        
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    Sprite* bullet = new Sprite(spriteSideFighterFireId, bulletFrame , getSideFightertBulletDstRect(), {0,0}, true, SUPER_ACE, fireAnimationFilm);
    assert(bullet);
    
    //play sound for fire
    SoundHolder::playSound("gunshot");
    
    //fireAnimation
    Animation* fireAnimation = AnimationHolder::getAnimationHolder()->getAnimation("superAceFire");
    assert(fireAnimation);
    
    MovingAnimator* fireAnimator = new MovingAnimator(animatorSideFighterFireId, bullet, (MovingAnimation*)fireAnimation);
    assert(fireAnimator);
    
    fireAnimator->start(Game::getGameTime());
    
    bullet->addCollisionHandler(Sprite::fireHandler());
}

void SuperAce::addSideFighters(){
    
    AnimationFilm* anim = AnimationFilmHolder::Get()->GetFilm("sideFighters");
    unsigned sideFighterFrameNo = 1;
    SDL_Rect sideFighterDstRect = { 0 , getDstRect().y , 3*(getDstRect().w/4) , getDstRect().h };
    SideFighter* sideFighter;
    
    /*right side fighter*/
    sideFighterDstRect.x = getDstRect().x+getDstRect().w;
    sideFighter = new SideFighter(this, RIGHT_FIGHTER, sideFighterFrameNo, sideFighterDstRect, _point, _isVisible, _type, anim);
    
    MovingPathAnimation* sideFighterAnimationRight = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationRight");
    MovingPathAnimator* sideFighterAnimatorRight = new MovingPathAnimator( "RightSideFighterAnimatorRight", sideFighter, sideFighterAnimationRight);
    
    MovingPathAnimation* sideFighterAnimationLeft	=(MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationLeft");
    MovingPathAnimator* sideFighterAnimatorLeft	= new MovingPathAnimator("RightSideFighterAnimatorLeft", sideFighter, sideFighterAnimationLeft);

    /*left side fighter*/
    sideFighterDstRect.x = getDstRect().x-sideFighterDstRect.w;
    sideFighter = new SideFighter(this, LEFT_FIGHTER, sideFighterFrameNo, sideFighterDstRect, _point, _isVisible, _type, anim);
    
    sideFighterAnimationRight = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationRight");
    sideFighterAnimatorRight = new MovingPathAnimator("LeftSideFighterAnimatorRight", sideFighter, sideFighterAnimationRight);
    
    sideFighterAnimationLeft = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationLeft");
    sideFighterAnimatorLeft	= new MovingPathAnimator("LeftSideFighterAnimatorLeft", sideFighter, sideFighterAnimationLeft);
    
    assert(getAttached(RIGHT_FIGHTER));
    assert(getAttached(LEFT_FIGHTER));
    
    assert(!getAttached(RIGHT_FIGHTER)->isOutOfWindow());
    assert(!getAttached(LEFT_FIGHTER)->isOutOfWindow());

}

