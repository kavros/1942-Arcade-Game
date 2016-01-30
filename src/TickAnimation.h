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
	template <typename Tfunc>
	
    void SetOnTick(const Tfunc& f){
		_onTick = f;
	}
    
	void SetForever(void){
		_repetitions = 0;
	}
    
	TickAnimation(animid_t id): Animation(id), _delay(0), _repetitions(1), _onTick(nullptr){
    
    }
    
    TickAnimation(animid_t id ,delay_t _delay ,unsigned _repetitions ,OnTick _onTick):
    Animation(id), _delay(_delay), _repetitions(_repetitions), _onTick(_onTick){
        
    }
    
    Animation* clone(animid_t newId) const{
        return new TickAnimation(newId);
    }
    
    ~TickAnimation(){}
    
    //getter
    delay_t getDelay(){
        return _delay;
    }
    
    OnTick getOnTick(){
        return _onTick;
    }

};
#endif
