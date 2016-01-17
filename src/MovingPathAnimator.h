#ifndef MOVINGPATHANIMATOR_H
#define MOVINGPATHANIMATOR_H

#include "Animator.h"
#include "MovingPathAnimation.h"
#include "Sprite.hpp"
#include "AnimatorHolder.h"
#include <assert.h>


class MovingPathAnimator :public Animator{
private:
	Sprite*					_sprite;
	MovingPathAnimation*	_anim;
    std::list<PathEntry>::const_iterator  _currPath;

public:
	void progress(timestamp_t currTime) override;
	
	//getters
	Sprite*					getSprite();
	MovingPathAnimation*	getMovingAnimationPath();

	void start(timestamp_t t);
	static void finishCallB(Animator* a,void*);
	
	//constructor
	MovingPathAnimator(std::string id,Sprite* sprite,MovingPathAnimation* anim);

    void checkAnimatorForDelete(void) override    ;

};


#endif