#include "SuperAce.h"

SuperAce::SuperAce(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm):
Sprite(id,frameNo,dstRect,point,isVisible,type,currFilm)
{

    _spriteId = id;
    _dstRect = dstRect;
    _point = point;
    setVisibility(isVisible);
    _type = type;
    _currFilm = currFilm;
    setFrame(frameNo);
	_state = STARTING;
    _superAceLives = 1;
    AnimationFilm* animationBulletFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(animationBulletFilm);
    
    bulletFrame = 2;
    _bulletDstRect.x=this->getDstRect().x + (this->getDstRect().w/4);
    _bulletDstRect.y=this->getDstRect().y - this->getDstRect().h;
    _bulletDstRect.w=animationBulletFilm->getFrameBox(bulletFrame).w * Game::getSpriteSize();
    _bulletDstRect.h=animationBulletFilm->getFrameBox(bulletFrame).h * Game::getSpriteSize();
    
    this->addCollisionHandler(Sprite::touchHandler());

}

void SuperAce::render(SDL_Renderer * renderer){
	display(renderer);
};

SDL_Rect SuperAce::getBulletDstRect(int frame){
    _bulletDstRect.x=(this->getDstRect().x + this->getDstRect().w/2 - _bulletDstRect.w/2);
    _bulletDstRect.y=this->getDstRect().y - this->getDstRect().h/3;
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
    _superAceLives = superAceLives;
}

void SuperAce::setSuperAceLoops(unsigned int superAceLoops){
    _superAceLoops = superAceLoops;
}

void SuperAce::setBulletFrame(unsigned int _bulletFrame){
    AnimationFilm* animationBulletFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(animationBulletFilm);
    
    bulletFrame = _bulletFrame;
    _bulletDstRect.w=animationBulletFilm->getFrameBox(bulletFrame).w * Game::getSpriteSize();
    _bulletDstRect.h=animationBulletFilm->getFrameBox(bulletFrame).h * Game::getSpriteSize();
}

void SuperAce::fire(void){

    static int number = 0;
    string spriteSuperAceFireId = "spriteSuperAceFire" + std::to_string (number);
    string animatorSuperAceFireId = "animatorSuperAceFire" + std::to_string (number);

    number++;
    
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    Sprite* bullet = new Sprite(spriteSuperAceFireId, bulletFrame, getBulletDstRect(bulletFrame), {0,0}, true, SUPER_ACE, fireAnimationFilm);
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
Sprite(id,frameNo,dstRect,point,isVisible,type,currFilm)
{
        
    ace->attach(this, id);
    
    _spriteId = id;
    _dstRect = dstRect;
    _point = point;
    setVisibility(isVisible);
    _type = type;
    _currFilm = currFilm;
    setFrame(frameNo);
    _state = STARTING;
    
    AnimationFilm* animationBulletFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(animationBulletFilm);
    
    sideFightertBulletDstRect.x=this->getDstRect().x + (_dstRect.w/4);
    sideFightertBulletDstRect.y=this->getDstRect().y - _dstRect.h;
    sideFightertBulletDstRect.w=animationBulletFilm->getFrameBox(1).w * Game::getSpriteSize();
    sideFightertBulletDstRect.h=animationBulletFilm->getFrameBox(1).h * Game::getSpriteSize();
    
    this->addCollisionHandler(Sprite::touchHandler());
}

SideFighter::~SideFighter(){
    detach(this->getId(),false);
}

SDL_Rect SideFighter::getSideFightertBulletDstRect(unsigned int bulletFrame){
    sideFightertBulletDstRect.x=(this->getDstRect().x + this->getDstRect().w/2 - sideFightertBulletDstRect.w/2);
    sideFightertBulletDstRect.y=this->getDstRect().y - _dstRect.h/3;
    return sideFightertBulletDstRect;
}

void SideFighter::fire (void) {
    
    /* spawn bullet */
    static int number = 0;
    string spriteSideFighterFireId = "spriteSideSuperAceFire" + std::to_string (number);
    string animatorSideFighterFireId = "animatorSideSuperAceFire" + std::to_string (number);
    
    number++;
    
    unsigned int bulletFrame = 1;
    
    /*bullet test*/
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    Sprite* bullet = new Sprite(spriteSideFighterFireId, bulletFrame , getSideFightertBulletDstRect(bulletFrame), {0,0}, true, SUPER_ACE, fireAnimationFilm);
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
    SDL_Rect sideFighterDstRect = {0,0,0,0};
    SideFighter* sideFighter;
    
    /*right side fighter*/
    sideFighter = new SideFighter(this, RIGHT_FIGHTER, sideFighterFrameNo, sideFighterDstRect, _point, _isVisible, _type, anim);
    sideFighterDstRect = { getDstRect().x+getDstRect().w , getDstRect().y , sideFighter->getDstRect().w , getDstRect().h };
    sideFighter->setDstRect(sideFighterDstRect);
    
    MovingPathAnimation* sideFighterAnimationRight = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationRight");
    MovingPathAnimator* sideFighterAnimatorRight = new MovingPathAnimator( "RightSideFighterAnimatorRight", sideFighter, sideFighterAnimationRight);
    
    MovingPathAnimation* sideFighterAnimationLeft	=(MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationLeft");
    MovingPathAnimator* sideFighterAnimatorLeft	= new MovingPathAnimator("RightSideFighterAnimatorLeft", sideFighter, sideFighterAnimationLeft);

    /*left side fighter*/
    sideFighter = new SideFighter(this, LEFT_FIGHTER, sideFighterFrameNo, sideFighterDstRect, _point, _isVisible, _type, anim);
    sideFighterDstRect = { getDstRect().x-sideFighter->getDstRect().w , getDstRect().y , sideFighter->getDstRect().w , getDstRect().h };
    sideFighter->setDstRect(sideFighterDstRect);
    
    
    sideFighterAnimationRight = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationRight");
    sideFighterAnimatorRight = new MovingPathAnimator("LeftSideFighterAnimatorRight", sideFighter, sideFighterAnimationRight);
    
    sideFighterAnimationLeft = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationLeft");
    sideFighterAnimatorLeft	= new MovingPathAnimator("LeftSideFighterAnimatorLeft", sideFighter, sideFighterAnimationLeft);
    
    assert(getAttached(RIGHT_FIGHTER));
    assert(getAttached(LEFT_FIGHTER));
}

