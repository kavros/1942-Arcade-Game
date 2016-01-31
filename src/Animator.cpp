#include "Animator.h"
#include "AnimatorHolder.h"

void Animator::start(timestamp_t t){
    
}

void Animator::stop(void){
    if (hasFinished()){
        _state = ANIMATOR_STOPPED;
        notifyStopped();
    }
}

bool Animator::hasFinished() const{
    if (_state == ANIMATOR_FINISHED) {
        return true;
    }else{
        return false;
    }
}
void Animator::notifyProgressed(void){
    if (_onProgress)
        (*_onProgress)(this, _progessClosure);
}
void Animator::notifyStopped(void){
    
    if (_onFinish)
        (*_onFinish)(this, _finishClosure);
    
}

void Animator::timeShift(timestamp_t offset)
{
    _lastTime += offset;
}

Animator::Animator(){
    assert(0);
}

Animator::Animator(animid_t id) :_id(id), _lastTime(0), _state(ANIMATOR_FINISHED), _onFinish((FinishCallback)0), _finishClosure((void*)0){
    AnimatorHolder::getAnimatorHolder()->Register(this);
}

Animator::~Animator(){
}

void Animator::setOnFinished(FinishCallback f,  void* c ){
    _onFinish =f;
    _finishClosure = c;
}

Animator::ProgressCallback Animator::getProgressCallback(void) const{
    return _onProgress;
}
void* Animator::getProgressClosure(void)const{
    return _progessClosure;
}
void Animator::setOnProgress(ProgressCallback f, void* c ){
    _onProgress = f;
    _progessClosure = c;
}

animid_t Animator::getId(){
    return _id;
}


void Animator::setState(enum animatorstate_t state){
	_state = state;
}

void Animator::destroyAnimator(){
	AnimatorHolder::getAnimatorHolder()->cancel(this);

	LatelyDestroyable::destroy();
}