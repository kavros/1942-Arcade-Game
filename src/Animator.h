#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "includes.h"
typedef unsigned long timestamp_t;
typedef std::string animid_t;
enum animatorstate_t{
	ANIMATOR_FINISHED	= 0,
	ANIMATOR_RUNNING	= 1,
	ANIMATOR_STOPPED	= 2
};

class Animator{
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
    
public:
	//functions apo lectures///////////////
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

	Animator();
	virtual ~Animator(){ };

    virtual void checkAnimatorForDelete(void) = 0;
};
#endif