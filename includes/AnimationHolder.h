#ifndef ANIMATIONHOLDER_H
#define ANIMATIONHOLDER_H

#include "../includes/Animation.h"
#include "../includes/includes.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <fstream>
#include "../includes/MovingPathAnimation.h"
#include "../includes/MovingAnimation.h"
#include "../includes/TickAnimation.h"

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
    void    LoadMovingPathAnim (const std::string& cataloge,int n);
};

#endif