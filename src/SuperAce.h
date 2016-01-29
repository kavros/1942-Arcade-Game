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

#define LEFT_FIGHTER  "left.fighter"
#define RIGHT_FIGHTER "right.fighter"

class SideFighter : public Sprite {
private:
    unsigned sideFighterWidth;
    unsigned sideFighterHeight;
    SDL_Rect sideFightertBulletDstRect;
public:
    
    //constructor
    SideFighter(Sprite* ace, const std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm);
    ~SideFighter();
    
    //get
    unsigned getSideFighterWidth();
    unsigned getSideFighterHeight();
    SDL_Rect getSideFightertBulletDstRect(int frame);
    
    //set
    void setSideFighterWidth(unsigned width);
    void setSideFighterHeight(unsigned height);
    
    //functionality
    void fire (void);
};


class SuperAce:public Sprite{
    
private:
    unsigned _superAceWidth;
    unsigned _superAceHeight;
    SDL_Rect _bulletDstRect;
    unsigned int _superAceLives;
    unsigned int _superAceLoops;
public:

	//constructor
    SuperAce(std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm);
	void handleEvent(SDL_Event e);
    
    virtual void filterMotion(int* dx, int* dy) const override;

	//Show the plane on the screen relative to the camera
	void render(SDL_Renderer * renderer);

	//get
    unsigned getSuperAceWidth();
    unsigned getSuperAceHeigth();
    SDL_Rect getBulletDstRect(int frame);
    unsigned int getSuperAceLives();
    unsigned int getSuperAceLoops();
    
    //set
    void setSuperAceWidth(unsigned width);
    void setSuperAceHeigth(unsigned height);
    void setSuperAceLives(unsigned int superAceLives);
    void setSuperAceLoops(unsigned int superAceLoops);
    
    //functionality
    void fire(void);
    void doManeuever(void);

};

#endif