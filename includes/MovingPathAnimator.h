#ifndef MOVINGPATHANIMATOR_H
#define MOVINGPATHANIMATOR_H

#include "../includes/Animator.h"
#include "../includes/MovingPathAnimation.h"
#include "../includes/Sprite.hpp"
#include "../includes/AnimatorHolder.h"
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
    void setAnimation(MovingPathAnimation* mp);
    
    void chooseCallBack(string id);

	void start(timestamp_t t) override;
	static void finishCallB(Animator* a,void*);
    static void nextAnimator(Animator* anim,void* b);
	
	//constructor
	MovingPathAnimator(std::string id,Sprite* sprite,MovingPathAnimation* anim);

    void checkAnimatorForDelete(void) override    ;

};


#endif