#include "TimerTickAnimator.h"

void TimerTickAnimator::start( timestamp_t t){
    
    this->_lastTime = t;
    if (getState() == ANIMATOR_RUNNING){
        assert(0);
    }
    setState(ANIMATOR_RUNNING);
    AnimatorHolder::markAsRunning(this);
}

TimerTickAnimator::TimerTickAnimator(TickAnimation* tick){
    tickAnimation = tick;
}

void TimerTickAnimator::progress(timestamp_t currTime){
    
    if( currTime >= _lastTime && currTime - _lastTime < tickAnimation->getDelay()  ){
        
        //timeShift ( tickAnimation->getDelay() );
    }
    else{

        _state = ANIMATOR_FINISHED;
        tickAnimation->getOnTick()();
        stop();
    }

    
}

void TimerTickAnimator::timeShift(timestamp_t offset){
    _lastTime+=offset;
}