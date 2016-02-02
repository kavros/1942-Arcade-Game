#ifndef MOVINGANIMATION_H
#define MOVINGANIMATION_H

#include <assert.h> 
#include "Animation.h"
class MovingAnimation : public Animation {
public:
	//getters
	delay_t		getDelay(void) const { return delay; }
	offset_t	getDy(void) const { return dy; }
	offset_t	getDx(void) const { return dx; }
	bool		getContinuous(void) const { return continuous; }

	//setters
	void		setDx(offset_t v) { dx = v; }
	void		setDy(offset_t v) { dy = v; }
	void		setDelay(delay_t v) { delay = v; }
	void		setContinuous(bool v) { continuous = v; }
	
	//clone
	Animation* clone(animid_t newId) const{
        assert(0);
		return new MovingAnimation(dx, dy, delay, continuous, newId);
	}

	//ctor
	MovingAnimation(
		offset_t _dx, offset_t _dy, delay_t _delay, bool c, animid_t _id
		) : dx(_dx), dy(_dy), delay(_delay), continuous(c), Animation(_id){}

private:
	offset_t dx, dy;	//orizei mia metakinisi se sygkekrimeno dx dy
	delay_t delay;		//parodos xronou tou opoiou i metakinisi tha efarmostei
	bool continuous; //orizei an h metakinisi auth epanalamvanetai synexws
};
#endif
