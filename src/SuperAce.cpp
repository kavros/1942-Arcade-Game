#include "SuperAce.h"

SuperAce::SuperAce(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm){
    
    struct touchHandler : public Sprite::CollisionHandler{
        void operator()(Sprite* aircraft,Sprite* arg) const{
            if(!aircraft || !arg)
                return;
            if( !aircraft->getVisibility() || !arg->getVisibility())
                return;
            
            aircraft->setVisibility(false);
            arg->setVisibility(false);
            
            aircraft->Destroy();
            arg->Destroy();
            
            AnimatorHolder::createExplosion( aircraft->getDstRect() );

        }
        touchHandler* Clone(void) const{
            return new touchHandler();
        }
        ~touchHandler(){};
    };

    _spriteId = id;
    _dstRect = dstRect;
    _point = point;
    _isVisible = isVisible;
    _type = type;
    _currFilm = currFilm;
    setFrame(frameNo);
    _superAceWidth= dstRect.w ;//_currFilm->getFrameBox(0).w;
    _superAceHeight= dstRect.h; //_currFilm->getFrameBox(0).h;
    
    
    AnimationFilm* animationBulletFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    
    _bulletDstRect.x=this->getDstRect().x + (this->getSuperAceWidth()/4);
    _bulletDstRect.y=this->getDstRect().y - this->getSuperAceHeigth();
    _bulletDstRect.w=animationBulletFilm->getFrameBox(2).w;
    _bulletDstRect.h=animationBulletFilm->getFrameBox(2).h;
    
    this->addCollisionHandler(touchHandler());

    SpritesHolder::getSpritesHolder()->add(this);
    
}

SuperAce::SuperAce(){

	AnimationFilmHolder *animation = AnimationFilmHolder::Get();
    
	_currFilm = animation->GetFilm("Super.Ace.1942");
	_isVisible = true;

	//set sprite size and positions on the screen
	setFrame(0);

    _superAceWidth=_currFilm->getFrameBox(0).w;
    _superAceHeight=_currFilm->getFrameBox(0).h;
    
	_dstRect.x = WIN_WIDTH / 2-_superAceWidth/2;
	_dstRect.y = WIN_HEIGHT - _superAceHeight;
	_dstRect.w = _superAceWidth;
	_dstRect.h = _superAceHeight;

	_type = SUPER_ACE;
    
	//set center of the picture up left 
	_point.x = 0;
	_point.y = 0;

    SpritesHolder::getSpritesHolder()->add(this);

    assert(0);
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

SDL_Rect SuperAce::getBulletDstRect(){
    
    _bulletDstRect.x=(this->getDstRect().x + this->getDstRect().w/3 + 2);
    _bulletDstRect.y=this->getDstRect().y - this->getSuperAceHeigth()/3;

    return _bulletDstRect;
}

//set
void SuperAce::setSuperAceWidth(unsigned width){
    _superAceWidth = width;
}

void SuperAce::setSuperAceHeigth(unsigned height){
    _superAceHeight = height;
}

void SuperAce::fire(void){

    struct fireHandler : public Sprite::CollisionHandler{
        void operator()(Sprite* bullet,Sprite* arg) const{
            if(!bullet || !arg)
                return;
            if( !bullet->getVisibility() || !arg->getVisibility())
                return;
            
            bullet->setVisibility(false);
            arg->setVisibility(false);
            
            bullet->Destroy();
            arg->Destroy();

            AnimatorHolder::createExplosion( arg->getDstRect() );
        }
        fireHandler* Clone(void) const{
            return new fireHandler();
        }
        ~fireHandler(){};
    };
    
    /*bullet test*/
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("bullets");
    assert(fireAnimationFilm);
    
    Sprite* bullet = new Sprite("spriteSuperAceFire", 2, getBulletDstRect(), {0,0}, true, SUPER_ACE, fireAnimationFilm);
    assert(bullet);
        
    //fireAnimation
    Animation* fireAnimation = AnimationHolder::getAnimationHolder()->getAnimation("superAceFire");
    assert(fireAnimation);
    
    MovingAnimator* fireAnimator = new MovingAnimator("animatorSuperAceFire", bullet, (MovingAnimation*)fireAnimation);
    
    AnimatorHolder::getAnimatorHolder()->Register(fireAnimator);

    fireAnimator->start(Game::getGameTime());
    
    bullet->addCollisionHandler(fireHandler());

    /*bullet test end*/

    if (auto* left = getAttached(LEFT_FIGHTER))
        static_cast<SideFighter*>(left)->Fire();
    if (auto* right = getAttached(RIGHT_FIGHTER))
        static_cast<SideFighter*>(right)->Fire();
}

void SuperAce::filterMotion(int* dx, int* dy) const {
    int old_x = _dstRect.x;
    int old_y = _dstRect.y;
    int new_x = _dstRect.x + *dx;
    int new_y = _dstRect.y + *dy;
        
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
