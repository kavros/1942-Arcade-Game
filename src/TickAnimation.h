#ifndef TICKANIMATION_H
#define TICKANIMATION_H

#include "Animation.h"
#include <functional>
#include <iostream>

class TickAnimation : public Animation {
public:
	using OnTick = std::function<void(void)>;
private:
	delay_t _delay;
	unsigned _repetitions; // 0 => forever
	OnTick _onTick;
public:

    //constructor
    TickAnimation(animid_t id);
    
    TickAnimation(animid_t id ,delay_t _delay ,unsigned _repetitions);

    TickAnimation(animid_t id ,delay_t _delay ,unsigned _repetitions ,OnTick _onTick);
    
    //destructor
    ~TickAnimation();
    
    //clone
    Animation* clone(animid_t newId) const;
    
    //getter
    delay_t getDelay();
    
    OnTick getOnTick();

    unsigned getRepetitions();
    
    //setter
    void setDelay(delay_t delay);
    
    void setOnTick(std::function<void(void)> f){
        _onTick = f;
    }
    
    void setForever(void);
    
    void setRepetitions(unsigned repetitions);
};
#endif
