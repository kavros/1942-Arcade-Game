#ifndef ANIMATORHOLDER_H
#define ANIMATORHOLDER_H

#include "Animator.h"
#include "includes.h"
#include "AnimationFilmHolder.hpp"
#include "SpritesHolder.hpp"
#include "AnimationHolder.h"
#include "MovingAnimator.h"
#include "Game.hpp"

class Animator;

typedef unsigned long timestamp_t;

class AnimatorHolder{
private:
    typedef std::map<std::string, Animator*> AnimatorMap;
    typedef std::list<Animator*> AnimatorList;
    
	class ProgressFunctor : public std::unary_function<Animator*, void> {
		timestamp_t _t;
	public:
        void operator()(Animator* a) const;
        ProgressFunctor(timestamp_t t);
	};

    AnimatorList _running, _suspended;
    AnimatorMap _map;
    static AnimatorHolder* _holder;
    
    AnimatorHolder();
    ~AnimatorHolder();

public:
    void Register(Animator* a);
    void cancel(Animator* a);
	
    //get
    static AnimatorHolder* getAnimatorHolder(){
        if (!_holder)
            _holder = new AnimatorHolder();
        return _holder;
    }
    
    static void cleanup(){
        _holder->~AnimatorHolder();
        _holder = NULL;
    }
    
	//marking state
    static void markAsRunning(Animator* a);
    static void markAsSuspended(Animator* a);

	//progress
    static void progress(timestamp_t currTime);
    
    static void checkAnimatorsForDelete(void);

    static unsigned long getTotalRunning();
    
    static unsigned long getTotalSuspended();

	static Animator* getAnimator(animid_t );
    
    static void triggerAnimators();

    static void createExplosion(SDL_Rect dstRect);

};

#endif