#ifndef ANIMATIONHOLDER_H

#define ANIMATIONHOLDER_H
#include "Animation.h"
#include "includes.h"
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include <fstream>
#include "MovingPathAnimation.h"
#include "MovingAnimation.h"
class AnimationHolder{
    
private:
	typedef std::map<animid_t, Animation*> Animations;

	static AnimationHolder* _holder;//singleton
    
    AnimationHolder();
    ~AnimationHolder();

    Animations _map;

public:
    static AnimationHolder* getAnimationHolder();
    
    static void cleanUp(void);
    
    void add(Animation* anim);
    
    Animation* getAnimation(animid_t id);
    void    Load (const std::string& cataloge);
};

#endif