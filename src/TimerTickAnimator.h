#ifndef TIMERTICKANIMATOR_H
#define TIMERTICKANIMATOR_H

#include "TickAnimation.h"
#include "Animator.h"

class TimerTickAnimator : public Animator {
public:
    
    //costructor
	TimerTickAnimator(TickAnimation* tick);
    
    //destructor
    ~TimerTickAnimator(){}

    //functionallity
    void progress(timestamp_t currTime);

    void timeShift(timestamp_t offset){
        _lastTime+=offset;
    }
    
    void checkAnimatorForDelete(void){}
    
};

#endif