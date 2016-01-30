#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "includes.h"
#include "LatelyDestroyable.h"

typedef unsigned long timestamp_t;
typedef std::string animid_t;

enum animatorstate_t{
	ANIMATOR_FINISHED	= 0,
	ANIMATOR_RUNNING	= 1,
	ANIMATOR_STOPPED	= 2,
	ANIMATOR_PAUSED		= 3
};

class Animator : public LatelyDestroyable{
public:
	typedef void(*ProgressCallback)(Animator* ,void*);
	typedef void(*FinishCallback) (Animator*, void*);

	
protected:
	animid_t                _id;
	timestamp_t				_lastTime;
	animatorstate_t			_state;
	ProgressCallback		_onProgress;
	FinishCallback			_onFinish;
	void*					_finishClosure;
    void*					_progessClosure;
    
	void notifyStopped(void);
    void notifyProgressed(void);
    
    virtual ~Animator();

public:
	//functions apo lectures///////////////
    virtual void start(timestamp_t t);
    
	void stop(void);

	bool hasFinished(void) const;

	virtual void timeShift(timestamp_t offset);

	virtual void progress(timestamp_t currTime) = 0;
    
    void setOnFinished(FinishCallback f, void* c = (void*) 0);

	/////////////////////////////////////////////////
    animid_t getId();
	//////////funcs  apo ekfwnisi ////////////////////
    ProgressCallback getProgressCallback(void) const;
    void* getProgressClosure(void)const;
    void setOnProgress(ProgressCallback f, void* c = (void*) 0);
	/////////////////////////////////////////////////


	enum animatorstate_t getState(){
		return _state;
	}
	void setState(enum animatorstate_t);
	timestamp_t getLastTime(){ return _lastTime; }

	Animator();

    virtual void checkAnimatorForDelete(void) = 0;
    
    void destroyAnimator();
};
#endif
