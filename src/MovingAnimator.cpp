#include "../includes/MovingAnimator.h"

void MovingAnimator::start( timestamp_t t){

	this->_lastTime = t;
	if (getState() == ANIMATOR_RUNNING){
		cout << "Error ANIMATOR is Still running" << endl;
        assert(0);
	}
	setState(ANIMATOR_RUNNING);
    AnimatorHolder::markAsRunning(this);
}

MovingAnimator::MovingAnimator(std::string id, Sprite* sprite, MovingAnimation* animation):
Animator(id){
    _sprite = sprite;
    _anim = animation;
};

void MovingAnimator::progress(timestamp_t currTime){
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
    
    if( (_sprite->isOutOfWindow() || _sprite->getState() == SpriteState::IN_COLUSION || this->getState() == ANIMATOR_STOPPED ) && _sprite->getId().compare("SuperAce0") != 0 && _sprite->getId().compare("SuperAce1") != 0 && _sprite->getType() != TERRAIN ){
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
