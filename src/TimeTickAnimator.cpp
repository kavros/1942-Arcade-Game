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
    
    if(!this->isAlive())
        return;
    
    assert(currTime >= _lastTime);
    
    if( currTime - _lastTime >= tickAnimation->getDelay()  ){
        
        if( tickAnimation->getOnTick() )
            tickAnimation->getOnTick()();

        _lastTime = currTime;
 
        if( tickAnimation->getRepetitions() != 0){
            tickAnimation->setRepetitions( tickAnimation->getRepetitions() - 1 );
            
            if( tickAnimation->getRepetitions() == 0){
                setState(ANIMATOR_FINISHED);
                setOnFinished(finishCallB);
            }
        }
    }
    
}

void TimerTickAnimator::checkAnimatorForDelete(void){

    if(!this->isAlive())
        return;
    
    if( tickAnimation->getRepetitions() == 0 && getState() == ANIMATOR_FINISHED ){

        tickAnimation = nullptr;
        
        this->destroyAnimator();
        
    }
    
}

void TimerTickAnimator::finishCallB(Animator* a,void* b){
    AnimatorHolder::markAsSuspended(a);
}