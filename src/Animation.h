#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>

class AnimationHolder;

typedef signed short offset_t;
typedef unsigned long delay_t;
typedef std::string animid_t;

class Animation {
public:
	//getter
	animid_t				getId(void) { return id; }
	
	//pure virtual  function
	virtual Animation*		clone(animid_t newId) const = 0;

	Animation(animid_t _id) : id(_id){
    }
	virtual ~Animation(){}

private:
	animid_t id;	//einai xrisimo gia na exoume grhgorh prosvash se opoiodhpote 
					//animation instance
};
#endif