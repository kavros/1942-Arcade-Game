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

void MovingPathAnimator::setAnimation(MovingPathAnimation* mp){
    _anim = mp;
    _currPath = _anim->getPath().begin();
}

void MovingPathAnimator::chooseCallBack(string id){
    std::size_t found;
    string* str = nullptr;
    
    
    
    found = id.find("MedGreenDoubleEngAnimator");
    if (found == 0)
        str = new string("Chain1"+ id);
    found = id.find("Chain1MedGreenDoubleEngAnimator");
    if (found == 0)
        str = new string("Chain2"+ id);
    found = id.find("Chain1MiniGreyOneEngAnimator");
    if (found == 0)
        str = new string("Chain2"+ id);
    
    found = id.find("MiniGreyOneEngAnimator");
    if (found == 0)
        str = new string("Chain1"+ id);
    
    //redJet
    found = id.find("RedJet");
    if (found == 0)
        str = new string("Chain1"+ id);
    found = id.find("Chain1RedJet");
    if (found == 0)
        str = new string("Chain2"+ id);
    found = id.find("Chain2Chain1RedJet");
    if (found == 0)
        str = new string("Chain3"+ id);
    found = id.find("Chain3Chain2Chain1RedJet");
    if (found == 0)
        str = new string("Chain4"+ id);
    
    //miniGreenOneEng
    found = id.find("MiniGreenOneEng");
    if (found == 0)
        str = new string("Chain1"+ id);
    found = id.find("Chain1MiniGreenOneEng");
    if (found == 0)
        str = new string("Chain2"+ id);
    
    
    //miniGreenDoubleEng
    found = id.find("MiniGreenDoubleEng");
    if (found == 0)
        str = new string("Chain1"+ id);
    found = id.find("Chain1MiniGreenDoubleEng");
    if (found == 0)
        str = new string("Chain2"+ id);
    found = id.find("Chain2Chain1MiniGreenDoubleEng");
    if (found == 0)
        str = new string("Chain3"+ id);
    found = id.find("Chain3Chain2Chain1MiniGreenDoubleEng");
    if (found == 0)
        str = new string("Chain4"+ id);
    
    //miniGreyDoubleEng
    found = id.find("MiniGreyDoubleEng");
    if (found == 0)
        str = new string("Chain1"+ id);
    found = id.find("Chain1MiniGreyDoubleEng");
    if (found == 0)
        str = new string("Chain2"+ id);
    found = id.find("Chain2Chain1MiniGreyDoubleEng");
    if (found == 0)
        str = new string("Chain3"+ id);
    found = id.find("Chain3Chain2Chain1MiniGreyDoubleEng");
    if (found == 0)
        str = new string("Chain4"+ id);
    
    //miniGreenJet
    found = id.find("MiniGreenJet");
    if (found == 0)
        str = new string("Chain1"+ id);
    found = id.find("Chain1MiniGreenJet");
    if (found == 0)
        str = new string("Chain2"+ id);
	//med grey
	found = id.find("MedGreyDoubleEngAnimator");
	if (found == 0)
		str = new string("Chain1" + id);
	found = id.find("Chain1MedGreyDoubleEngAnimator");
	if (found == 0)
		str = new string("Chain2" + id);

    //BigGreen + BigGrey
    found = id.find("Big");
    if (found == 0)
        str = new string("Chain1"+ id);
    found = id.find("Chain1Big");
    if (found == 0)
        str = new string("Chain2"+ id);

    if(str!=nullptr)
        setOnFinished(nextAnimator,(void*)str);
}

void MovingPathAnimator::progress(timestamp_t currTime){

	while ( (currTime > _lastTime ) && (currTime - _lastTime >= _currPath->_delay)){


        _sprite->move(_currPath->_dx, _currPath->_dy);
		_sprite->setFrame(_currPath->_frame);
        if(_sprite->isAlive())
            _sprite->setVisibility(_currPath->_visibility);

        _lastTime += (_currPath->_delay);
        //cout << "Curr time = " << currTime << "\tlast time = " << _lastTime << "\n";

		if (_anim->getPath().size() > 1){
			_currPath++;
		}
        if(_currPath == _anim->getPath().end() && !_anim->getContinuous()){
			
			//!!! only Maneuver Animation can change state from maneuever to Flying 
			if (_sprite->getState() == MANEUVER){
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
MovingPathAnimation* MovingPathAnimator::getMovingPathAnimation(){
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
    /*
    if( (_sprite->isOutOfWindow() || _sprite->getState() == SpriteState::IN_COLUSION || this->getState() == ANIMATOR_STOPPED ) && _sprite->getId().compare("SuperAce0") != 0 &&  _sprite->getId().find("SideFighter") == string::npos ){
        // doesnt contains SideFighter
        // it is not SuperAce0
        */
    if(   (_sprite->isOutOfWindow() || _sprite->getState() == SpriteState::IN_COLUSION || this->getState() == ANIMATOR_STOPPED ) && _sprite->getId().compare("SuperAce0") != 0){
        
        
        if( _sprite->getParent() ){
            if(_sprite->getParent()->getId().compare("SuperAce0") == 0){
                return;
            }
        }
        
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
