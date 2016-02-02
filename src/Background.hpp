
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
    
    //constructor destructor
    Background();
    Background(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm);
    ~Background();
    
public:

    static Background* Get();
    static Background* Get(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm);
    
    static void InitBackground();

    void initBackgroundObjects();
    
    void addBackgroundObject(string id);
    
    void moveBackground(int dx, int dy);

    void moveTerrainObjects(int dx, int dy);

    virtual void filterMotion(int* dx, int* dy) const override;
    
    void displayTerrain(SDL_Renderer* renderer);
    
    SpriteList getVisibleObjects();
};


#endif /* background_hpp */