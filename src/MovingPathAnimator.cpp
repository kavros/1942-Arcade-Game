#include "MovingPathAnimator.h"

//ctor
MovingPathAnimator::MovingPathAnimator(std::string id, Sprite* sprite,MovingPathAnimation* anim){
	_id = id;
	_sprite = sprite;
	_anim = anim;
    _currPath = _anim->getPath().begin();

	/*
	//!!!prepei na pernw to dx dy apo ton SuperAce
	PathEntry upsidePath;
	upsidePath._dx = 0;
	upsidePath._dy = 6;
	
	PathEntry upsidePath;
	upsidePath._dx = 0;
	upsidePath._dy = 6;
	*/

}

void MovingPathAnimator::progress(timestamp_t currTime){
	//cout << _anim->getPath().begin()->_delay << endl;
	/*if (_state == ANIMATOR_RUNNING){
		return;
	}*/
	
	while ( (currTime > _lastTime ) && (currTime - _lastTime >= _currPath->_delay)){
        
        _sprite->move(_currPath->_dx, _currPath->_dy);
		_sprite->setFrame(_currPath->_frame);
        if(_sprite->isAlive())
            _sprite->setVisibility(_currPath->_visibility);
        _lastTime += (_currPath->_delay);
        //cout << "Curr time = " << currTime << "\tlast time = " << _lastTime << "\n";
        _currPath++;
        if(_currPath == _anim->getPath().end()){
            _state = ANIMATOR_FINISHED;
            setOnFinished(finishCallB);
            stop();
            break ;
        }
        
	}
	
	if (_sprite->getState() == MANEUVER){
		_sprite->setState(FLYING);
	}
	
}




//geters
Sprite* MovingPathAnimator::getSprite(){
	return _sprite;
}
MovingPathAnimation* MovingPathAnimator::getMovingAnimationPath(){
	return _anim;
}

//start
void MovingPathAnimator::start(timestamp_t t){	
	 _currPath = _anim->getPath().begin();
	_lastTime = t;

	if (_state == ANIMATOR_RUNNING){
		//cout << "Error ANIMATOR is Still running" << endl;
		return;
	}
	
	_state = ANIMATOR_RUNNING;
	AnimatorHolder::markAsRunning(this);
}


//callback
void MovingPathAnimator::finishCallB(Animator* anim,void* b){
	AnimatorHolder::markAsSuspended(anim);
}

void MovingPathAnimator::checkAnimatorForDelete(void){
    
    assert(_sprite && _anim);
    
    if( _sprite->isOutOfWindow() || !_sprite->isAlive()){
        
        //stop the animator
        _state = ANIMATOR_FINISHED;
        setOnFinished(finishCallB);
        stop();
        
        AnimatorHolder::getAnimatorHolder()->cancel(this);
        _anim = nullptr; 
        _sprite = nullptr;
        
        //delete MovingAnimator
        this->~MovingPathAnimator();
    }
    
}
