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
    bool                    _continuous;
    std::list<PathEntry>::const_iterator  _currPath;

public:
	void progress(timestamp_t currTime) override;
	
	//getters
	Sprite*					getSprite();
	MovingPathAnimation*	getMovingPathAnimation();

    //setters
    void setContinuous(bool b);
    
    
    void chooseCallBack(string id);

	void start(timestamp_t t) override;
	static void finishCallB(Animator* a,void*);
    static void nextAnimator(Animator* anim,void* b);
	
	//constructor
	MovingPathAnimator(std::string id,Sprite* sprite,MovingPathAnimation* anim);

    void checkAnimatorForDelete(void) override    ;

};


#endif