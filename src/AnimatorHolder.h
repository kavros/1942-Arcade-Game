#ifndef ANIMATORHOLDER_H
#define ANIMATORHOLDER_H

#include "Animator.h"
#include "includes.h"
#include "AnimationFilmHolder.hpp"
#include "SpritesHolder.hpp"
#include "AnimationHolder.h"
#include "MovingAnimator.h"
#include "Game.hpp"
#include "EnemyFighter.hpp"

#include "TickAnimation.h"
#include "TimerTickAnimator.h"

class Animator;

typedef unsigned long timestamp_t;

typedef std::map<std::string, Animator*> AnimatorMap;
typedef std::list<Animator*> AnimatorList;

class AnimatorHolder{
private:

    
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
    
    static bool movingEnable;
    
    static void Register(Animator* a);
    static void cancel(Animator* a);
	
    //get
    static AnimatorHolder* getAnimatorHolder();
    static void stopSuperAceMovingAnimator();
    
	static void updateAllGreyPlaneAnimations();

	
	static void updateAllGreyJetsAnimations();


    static void cleanup();
    
	//marking state
    static void markAsRunning(Animator* a);
    static void markAsSuspended(Animator* a);

	//progress
    static void progress(timestamp_t currTime);
    
    static void checkAnimatorsForDelete(void);
    
    static unsigned long getTotalRunning();
    
    static unsigned long getTotalSuspended();

	static Animator* getAnimator(animid_t );
    
    static void triggerBullets();

    static void createExplosion(SDL_Rect dstRect);

	static void wakeUpAnimators(timestamp_t offset);
	static void pauseAnimators();
    static void Load (const std::string& cataloge);
    static void startTimeTickAnimators();
    
    static void triggerStartOfStageAnimators();
    static void triggerEndOfStageAnimators();
    static void triggerstartEnemyPlanesTickAnimator();
    static void superAceMovingAnimator();
    static void createUpdateScoreAnimator(SDL_Rect rect,int points);
    static bool updateSideFighterAnimation(string fighter);
    static bool onManuevuer();

};

#endif