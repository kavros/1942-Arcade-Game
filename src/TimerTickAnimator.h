#ifndef TIMERTICKANIMATOR_H
#define TIMERTICKANIMATOR_H

#include "TickAnimation.h"
#include "Animator.h"
#include "AnimatorHolder.h"

class TimerTickAnimator : public Animator {
    
private:
    TickAnimation*		tickAnimation;

public:
    
    //costructor
	TimerTickAnimator(animid_t id, TickAnimation* tick);
    
    //destructor
    ~TimerTickAnimator(){}

    //functionallity
    void start( timestamp_t t) override;

    void progress(timestamp_t currTime) override;
    
    void checkAnimatorForDelete(void) override;
    
    static void finishCallB(Animator* a,void* b);
    
    static void startTimeTickAnimator(animid_t id, std::function<void(void)> f);

    static void stopTimeTickAnimator(animid_t id);

};

#endif