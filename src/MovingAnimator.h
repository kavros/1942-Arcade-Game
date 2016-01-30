#ifndef MOVINGANIMATOR_H
#define MOVINGANIMATOR_H

#include "Animator.h"
#include "Sprite.hpp"
#include "MovingAnimation.h"
#include "AnimatorHolder.h"
#include "SpritesHolder.hpp"

// Also update subclasses to call NotifyProgressed in Progress
class MovingAnimator :public Animator{
private:
	Sprite*					_sprite;
	MovingAnimation*		_anim;

public:
	
	void progress(timestamp_t currTime) override;
	
	//getters
	Sprite*				getSprite();
	MovingAnimation*	getMovingAnimation();

	void start( timestamp_t t) override;
    static void finishCallB(Animator* a,void* b);
	MovingAnimator(void);
    MovingAnimator(std::string id,Sprite* sprite, MovingAnimation* animation);
	~MovingAnimator(){}
    
    void checkAnimatorForDelete(void) override;

};
#endif