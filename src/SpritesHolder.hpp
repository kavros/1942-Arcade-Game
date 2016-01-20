#ifndef SpritesHolder_hpp
#define SpritesHolder_hpp

#include "includes.h"
#include "Sprite.hpp"
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "Background.hpp"
#include <iostream>
#include <string>
#include <fstream>

typedef std::list<Sprite*> SpriteList;
typedef std::map<SpriteType,SpriteList*> SpriteByType;

class SpritesHolder{
private:

    static SpritesHolder* _holder;

    SpriteByType _sprites;

    SpritesHolder();
    ~SpritesHolder();

public:
    void add(Sprite *s);
    void remove(Sprite *s);
    void displayGameSprites(SDL_Renderer* renderer);
    SpriteList * getSprites(SpriteType type);
    Sprite* getSprite(SpriteType type, std::string id);
    
    void printSprites(SpriteType type);
    
    static  SpritesHolder* getSpritesHolder();
    
    void displaySprites(SDL_Renderer* renderer, SpriteType type);
        
    void CleanUp(void);

    void Load (const std::string& cataloge/*,SDL_Renderer* _renderer*/);
    
    static void checkSpritesForDelete();

};

#endif /* SpritesHolder_hpp */
