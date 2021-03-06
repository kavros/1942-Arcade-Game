
#ifndef background_hpp
#define background_hpp

#include "includes.h"
#include "Sprite.hpp"
#include "AnimationFilm.hpp"

#include "AnimationFilmHolder.hpp"
#include "SpritesHolder.hpp"
#include "AnimationHolder.h"
#include "AnimatorHolder.h"

class Background : public Sprite{
private:
    
    typedef std::list<Sprite*> SpriteList;
    SpriteList* _terrainObjects;

    static Background* _holder;
    
public:

    //constructor destructor
    Background();
    Background(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm);
    ~Background();

    static Background* Get();
    
    static void initBackgroundObjects();
    
    static void startBackgroundObjectAnimators();
    static void startBackgroundObjectAnimator(string id);

    void addBackgroundObject(string id);
    
    virtual void filterMotion(int* dx, int* dy) const override;
    
    static void displayTerrain(SDL_Renderer* renderer);
    
};


#endif /* background_hpp */