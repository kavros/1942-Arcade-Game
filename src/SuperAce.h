#ifndef SuperAce_hpp
#define SuperAce_hpp

#include "includes.h"

#include "Sprite.hpp"
#include "AnimationFilm.hpp"
#include "AnimationFilmHolder.hpp"
#include "SpritesHolder.hpp"
#include "MovingAnimator.h"
#include "AnimationHolder.h"
#include "Game.hpp"

using namespace std;

#define LEFT_FIGHTER  "left.fighter"
#define RIGHT_FIGHTER "right.fighter"

class SideFighter : public Sprite {
public:
    SideFighter(Sprite* ace, const std::string& name){
        ace->attach(this, name);
    }
    void Fire (void) {
        /* spawn bullet */
    }
};


class SuperAce:public Sprite{
    
private:
    int _dx, _dy;
    unsigned _superAceWidth;
    unsigned _superAceHeight;
    
public:

	//constructor
    SuperAce();

	void handleEvent(SDL_Event e);
    
    virtual void filterMotion(int* dx, int* dy) const override;

	//Show the plane on the screen relative to the camera
	void render(SDL_Renderer * renderer);

	//get
    unsigned getSuperAceWidth();
    unsigned getSuperAceHeigth();
    
    //set
    void setSuperAceWidth(unsigned width);
    void setSuperAceHeigth(unsigned height);
        
    void fire(void);
        
};

#endif