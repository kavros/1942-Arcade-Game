
#ifndef background_hpp
#define background_hpp

#include "includes.h"
#include "Sprite.hpp"
#include "AnimationFilm.hpp"
#include "AnimationFilmHolder.hpp"
#include "SpritesHolder.hpp"

class Background : public Sprite{
private:
    int _terrainWidth,_terrainHeight;
    
    typedef std::list<Sprite*> SpriteList;
    SpriteList* _terrainObjects;

    static Background* _holder;
    
    //constructor destructor
    Background();
    ~Background();
    
public:

    static Background* Get(){
        if (!_holder)
            _holder = new Background();
        return _holder;
    }

    void initBackgroundObjects();
    
    void addBackgroundObject(string id);
    
    void moveBackground(int dx, int dy);

    void moveTerrainObjects(int dx, int dy);

    virtual void filterMotion(int* dx, int* dy) const override;
    
    void displayTerrain(SDL_Renderer* renderer);
    
    SpriteList getVisibleObjects();
};


#endif /* background_hpp */