
#include "TickAnimation.h"

TickAnimation::TickAnimation(animid_t id): Animation(id), _delay(0), _repetitions(1), _onTick(nullptr){
    
}

TickAnimation::TickAnimation(animid_t id ,delay_t delay ,unsigned repetitions):
Animation(id), _delay(delay), _repetitions(repetitions), _onTick(nullptr){
    
}

TickAnimation::TickAnimation(animid_t id ,delay_t _delay ,unsigned repetitions ,OnTick _onTick):
Animation(id), _delay(_delay), _repetitions(repetitions), _onTick(_onTick){
    
}

TickAnimation::~TickAnimation(){}

Animation* TickAnimation::clone(animid_t newId) const{
    return new TickAnimation(newId);
}


//getter
delay_t TickAnimation::getDelay(){
    return _delay;
}

TickAnimation::OnTick TickAnimation::getOnTick(){
    return _onTick;
}

unsigned TickAnimation::getRepetitions(){
    return _repetitions;
}

//setter
void TickAnimation::setDelay(delay_t delay){
    _delay = delay;
}

void TickAnimation::setForever(void){
    _repetitions = 0;
}

void TickAnimation::setRepetitions(unsigned repetitions){
    _repetitions = repetitions;
}
