#include "MovingPathAnimator.h"

//ctor
MovingPathAnimator::MovingPathAnimator(std::string id, Sprite* sprite,MovingPathAnimation* anim):
Animator(id){
	_sprite = sprite;
	_anim = anim;
    _currPath = _anim->getPath().begin();
    setOnFinished(finishCallB);
    chooseCallBack(id);
    

}

void MovingPathAnimator::chooseCallBack(string id){
    std::size_t found;
    string* str = nullptr;
    
    found = id.find("RedJetAnimator");
    if (found == 0)
        str = new string("Circle"+ id);
    found = id.find("CircleRedJetAnimator");
    if (found == 0)
        str = new string("Straight"+ id);
    found = id.find("StraightCircleRedJetAnimator");
    if (found == 0)
        str = new string("Circle"+ id);
    found = id.find("CircleStraightCircleRedJetAnimator");
    if (found == 0)
        str = new string("Straight"+ id);
    
    if(str!=nullptr)
        setOnFinished(nextAnimator,(void*)str);
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
        if(_currPath == _anim->getPath().end() && !_anim->getContinuous()){
			
			//!!! only Maneuver Animation can change state from maneuever to Flying 
			if (_sprite->getState() == MANEUVER && getId() == "SuperAceAnimatorManeuver"){
				cout << "Super Ace state is now FLYING" << endl;
				_sprite->setState(FLYING);
			}
			_state = ANIMATOR_FINISHED;
            //setOnFinished(finishCallB);
            stop();

			
            break ;
        }else if(_anim->getContinuous() && _currPath == _anim->getPath().end() ){
            _currPath = _anim->getPath().begin();
        }
        
	}
    
     
     if (_sprite->getState() == STARTING){
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

//setters
void MovingPathAnimator::setContinuous(bool b){
    _continuous = b;
}

//start
void MovingPathAnimator::start(timestamp_t t){	
	 _currPath = _anim->getPath().begin();
	 _lastTime = t;

	if (getState() == ANIMATOR_RUNNING){
		//cout << "Error ANIMATOR is Still running" << endl;
		return;
	}
	
	_state = ANIMATOR_RUNNING;

	AnimatorHolder::markAsRunning(this);
	
}


void MovingPathAnimator::nextAnimator(Animator* anim,void* b){
    AnimatorHolder::markAsSuspended(anim);
    Sprite* sp = ((MovingPathAnimator*)anim)->getSprite();
    if(b != nullptr && sp->getState() != IN_COLUSION && !sp->isOutOfWindow() && sp->isAlive()){
        string* id = (string*)b;
        MovingPathAnimator* mpar = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator(*  id);
        assert(mpar);
        mpar->start(Game::getGameTime());
    }
}

//callback
void MovingPathAnimator::finishCallB(Animator* anim,void* b){
	AnimatorHolder::markAsSuspended(anim);
}

void MovingPathAnimator::checkAnimatorForDelete(void){
    
    assert(_sprite && _anim );
    
    if( (_sprite->isOutOfWindow() || _sprite->getState() == SpriteState::IN_COLUSION) && _sprite->getId().compare("SuperAce") != 0){
        //stop the animator
        _state = ANIMATOR_FINISHED;
        //setOnFinished(finishCallB);
        stop();
        
        AnimatorHolder::getAnimatorHolder()->cancel(this);
        _anim = nullptr; 
        _sprite = nullptr;
        
        //delete MovingAnimator
        this->destroyAnimator();
    }
    
}
