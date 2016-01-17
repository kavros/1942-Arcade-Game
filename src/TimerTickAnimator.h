#ifndef TIMERTICKANIMATOR_H
#define TIMERTICKANIMATOR_H

#include "TickAnimation.h"
#include "Animator.h"

class TimerTickAnimator : public Animator {
public:
	void progress(timestamp_t currTime);
	TimerTickAnimator(TickAnimation* tick);
};

#endif