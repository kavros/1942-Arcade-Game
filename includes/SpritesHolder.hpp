#ifndef SpritesHolder_hpp
#define SpritesHolder_hpp

#include "../includes/includes.h"
#include "../includes/Sprite.hpp"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "../includes/Background.hpp"
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
    static void add(Sprite *s);
    static void remove(Sprite *s);
    static void displayGameSprites(SDL_Renderer* renderer);
    static SpriteList * getSprites(SpriteType type);
    static Sprite* getSprite(SpriteType type, std::string id);
    
    static void printSprites(SpriteType type);
    
    static  SpritesHolder* getSpritesHolder();
    
    static void displaySprites(SDL_Renderer* renderer, SpriteType type);
        
    static void cleanUp(void);

    static void Load (const std::string& cataloge/*,SDL_Renderer* _renderer*/);
    
    static void checkSpritesForDelete();

    static bool uniqueAliveFromTeam(Sprite* sprite);

    static void smallAndBigEnemyFireEnable();

};

#endif /* SpritesHolder_hpp */
