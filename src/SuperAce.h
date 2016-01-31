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

class SideFighter : public Sprite {
private:
    SDL_Rect sideFightertBulletDstRect;
    unsigned bulletFrame;
public:
    
    //constructor
    SideFighter(Sprite* ace, const std::string id, unsigned  frameNo,SDL_Rect dstRect,SDL_Point point,bool isVisible,SpriteType type,AnimationFilm* currFilm);
    ~SideFighter();
    
    //get
    SDL_Rect getSideFightertBulletDstRect(unsigned int bulletFrame);
    
    //set
    
    //functionality
    void fire (void);
};


class SuperAce:public Sprite{
    
private:
    unsigned int bulletFrame;
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
    SDL_Rect getBulletDstRect(int frame);
    unsigned int getSuperAceLives();
    unsigned int getSuperAceLoops();
    unsigned int getBulletFrame();
    
    //set
    void setSuperAceLives(unsigned int superAceLives);
    void setSuperAceLoops(unsigned int superAceLoops);
    void setBulletFrame(unsigned int bulletFrame);
    
    //functionality
    void fire(void);
    void doManeuever(void);
    void addSideFighters();
};

#endif