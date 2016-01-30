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
	TimerTickAnimator(TickAnimation* tick);
    
    //destructor
    ~TimerTickAnimator(){}

    //functionallity
    void start( timestamp_t t) override;

    void progress(timestamp_t currTime) override;

    void timeShift(timestamp_t offset) override;
    
    void checkAnimatorForDelete(void) override{
    }
    
};

#endif