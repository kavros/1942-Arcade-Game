#include "AnimatorHolder.h"

AnimatorHolder* AnimatorHolder::_holder = 0;

void AnimatorHolder::Register(Animator* a) {
    _holder->_map[a->getId()] = a;
    _holder->_suspended.push_back(a);
}
void AnimatorHolder::cancel(Animator* a) {
    _holder->_suspended.remove(a);
}

//marking state
void AnimatorHolder::markAsRunning(Animator* a)	{

    AnimatorHolder::getAnimatorHolder()->_suspended.remove(a);
    AnimatorHolder::getAnimatorHolder()->_running.push_back(a);
    
}
void AnimatorHolder::markAsSuspended(Animator* a){

    AnimatorHolder::getAnimatorHolder()->_running.remove(a);
    AnimatorHolder::getAnimatorHolder()->_suspended.push_back(a);
    
}

void AnimatorHolder::progress(timestamp_t currTime) {
    AnimatorHolder* h = AnimatorHolder::getAnimatorHolder();

	AnimatorList::iterator it = h->_running.begin();
    AnimatorList::iterator it2;
	while (it != h->_running.end()){
		it2 = it;
		it2++;
		(*it)->progress(currTime);
		it = it2;
	}

}

void AnimatorHolder::checkAnimatorsForDelete(void){
    AnimatorHolder* h = AnimatorHolder::getAnimatorHolder();

    AnimatorList::iterator it = h->_running.begin();
    AnimatorList::iterator it2;
    while (it != h->_running.end()){
        it2 = it;
        it2++;
        (*it)->checkAnimatorForDelete();
        it = it2;
    }
    
    it = h->_suspended.begin();
    while (it != h->_suspended.end()){
        it2 = it;
        it2++;
        (*it)->checkAnimatorForDelete();
        it = it2;
    }

    return;
}

unsigned long AnimatorHolder::getTotalRunning(){
    
    return AnimatorHolder::getAnimatorHolder()->_running.size();
}

unsigned long AnimatorHolder::getTotalSuspended(){
    return AnimatorHolder::getAnimatorHolder()->_suspended.size();
}


AnimatorHolder::AnimatorHolder(){
    AnimatorHolder::_running.clear();
    AnimatorHolder::_suspended.clear();
}

AnimatorHolder::~AnimatorHolder(){
    AnimatorHolder::_running.clear();
    AnimatorHolder::_suspended.clear();
}

Animator* AnimatorHolder::getAnimator(animid_t id){
    return _holder->_map[id];
}

void AnimatorHolder::triggerAnimators(){
    static int i=0;
    if(i%100 == 0 && i < 1000 && i > 10){
                
        SDL_Rect dstRect;
        dstRect.x=WIN_WIDTH/2;
        dstRect.y=10;
        dstRect.w=32;
        dstRect.h=31;
        
        AnimationFilm* animationFilm = AnimationFilmHolder::Get()->GetFilm("green_jet");
        assert(animationFilm);
        
        Sprite* sprite = SpritesHolder::getSpritesHolder()->getSprite(SpriteType::ALIEN_SHIP, "GreenJet" + std::to_string(i)); //new Sprite("spriteStraightEnemyAttack", 0, dstRect, {0,0}, true, ALIEN_SHIP, fireAnimationFilm);
        
        assert(sprite);
        
        Animation* animation = AnimationHolder::getAnimationHolder()->getAnimation("green_jet_changing_down");
        assert(animation);
        
        MovingPathAnimator* animator = new MovingPathAnimator(string("animatorStraightEnemyAttack") + std::to_string(i), sprite, (MovingPathAnimation*)animation);
        AnimatorHolder::getAnimatorHolder()->Register(animator);
        cout<<"AAAAAAA"<<std::endl;
        animator->start(Game::getGameTime());
        
    }
    i++;

}

void AnimatorHolder::createExplosion(SDL_Rect dstRect){
    
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("explosion");
    assert(fireAnimationFilm);
    
    Sprite* explosion = new Sprite("explosionSprite", 0, dstRect, {0,0}, true, POWER_UPS, fireAnimationFilm);
    assert(explosion);
    
    Animation* explosionAnimation = AnimationHolder::getAnimationHolder()->getAnimation("explosion");
    assert(explosionAnimation);
    
    MovingPathAnimator* explosionAnimator = new MovingPathAnimator("animatorExplosion", explosion, (MovingPathAnimation*)explosionAnimation);
    
    AnimatorHolder::getAnimatorHolder()->Register(explosionAnimator);
    
    explosionAnimator->start(Game::getGameTime());
    
}
