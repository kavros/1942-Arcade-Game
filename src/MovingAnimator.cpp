#include "MovingAnimator.h"

void MovingAnimator::start( timestamp_t t){

	this->_lastTime = t;
	if (_state == ANIMATOR_RUNNING){
		cout << "Error ANIMATOR is Still running" << endl;
        assert(0);
	}
	_state = ANIMATOR_RUNNING;
    AnimatorHolder::markAsRunning(this);
}
/*
MovingAnimator::MovingAnimator(void) :
_sprite((Sprite*)0), _anim((MovingAnimation*)0){}
*/
MovingAnimator::MovingAnimator(std::string id, Sprite* sprite, MovingAnimation* animation){
    _id = id;
    _sprite = sprite;
    _anim = animation;
};

void MovingAnimator::progress(timestamp_t currTime){
	//cout << "progress" << endl;
	
    /*
    _sprite->move(_anim->getDx(), _anim->getDy());
    _state = ANIMATOR_FINISHED;
    setOnFinished(finishCallB);
	
    stop();
    
	*/
    
    assert(_anim && _sprite);
	while ( (currTime > _lastTime) && (currTime - _lastTime >= _anim->getDelay()) ){
		
        _sprite->move(_anim->getDx(), _anim->getDy());

        if (!_anim->getContinuous()){
            

            _state = ANIMATOR_FINISHED;
            setOnFinished(finishCallB);
            stop();
            
            break;
        }
        else{

            _lastTime += _anim->getDelay();
        }
        
	}

}

void MovingAnimator::finishCallB(Animator* a,void* b){
    AnimatorHolder::markAsSuspended(a);
}


MovingAnimation* MovingAnimator::getMovingAnimation(){
	return _anim;
}

Sprite* MovingAnimator::getSprite(){
	return _sprite;
}

void MovingAnimator::checkAnimatorForDelete(void){

    assert(_sprite && _anim);
    
    if( _sprite->isOutOfWindow()){

        //stop the animator
        _state = ANIMATOR_FINISHED;
        setOnFinished(finishCallB);
        stop();
        
        _anim = nullptr;
        _sprite = nullptr;
        
        //delete MovingAnimator
        this->destroyAnimator();
    }
    
}

