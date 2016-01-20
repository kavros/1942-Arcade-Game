
#include "SuperAce.h"
#include "SpritesHolder.hpp"
 SpritesHolder* SpritesHolder::_holder;

SpritesHolder::SpritesHolder(){
    
    SpriteType type;
    
    for(type=SpriteType(0); type <= SpriteType(SPRITE_TYPE_SIZE); type = SpriteType(type+1)){
        _sprites[type] = new SpriteList();
    }

}

SpritesHolder::~SpritesHolder(){
    _holder->_sprites.clear();
}

void SpritesHolder::add(Sprite *s){
    assert(s && s->getType()>=0 && s->getType()<= SPRITE_TYPE_SIZE);
   /*
    if (_sprites[s->getType()] == nullptr) {
        _sprites[s->getType()] = new SpriteList();
    }
    */
    _sprites[s->getType()]->push_back(s);
    
}

void SpritesHolder::remove(Sprite *s){
    _sprites[s->getType()]->remove(s);
}

Sprite* SpritesHolder::getSprite(SpriteType type, std::string id){
   SpriteList* sl = SpritesHolder::getSprites(type);
    for (std::list<Sprite*>::iterator it=sl->begin(); it != sl->end(); ++it){
        
        if((*it)->getId().compare(id) == 0)
            return *it;
    }
    cout<<"There is No Sprite with this id"<<std::endl;
    return nullptr;
}

void SpritesHolder::printSprites(SpriteType type){
    SpriteList* sl = SpritesHolder::getSprites(type);
    cout<<endl<<endl;
    for (std::list<Sprite*>::iterator it=sl->begin(); it != sl->end(); ++it){
        cout<<(*it)->getId()<<endl;
    }
    cout<<endl<<endl;
}

SpritesHolder* SpritesHolder::getSpritesHolder(){
    if (!SpritesHolder::_holder){
        SpritesHolder::_holder = new SpritesHolder();
    }
    return SpritesHolder::_holder;
}

SpriteList * SpritesHolder::getSprites(SpriteType type){
    assert(type>=0 && type<=SPRITE_TYPE_SIZE);

    SpriteByType::const_iterator i = _sprites.find(type);
    
    return i != _sprites.end() ? i->second : nullptr;
    
}

void SpritesHolder::displaySprites(SDL_Renderer* renderer, SpriteType type){
    assert(type>=0 && type<=SPRITE_TYPE_SIZE);
    
    SpriteList* sl = SpritesHolder::getSprites(type);
    if(!sl){
        return;
    }
    
    for (std::list<Sprite*>::iterator it=sl->begin(); it != sl->end(); ++it){
        if((*it)->getVisibility() == true){
           (*it)->display(renderer); 
        }
    }
    
}

void SpritesHolder::displayGameSprites(SDL_Renderer* renderer){
    assert(renderer);
    Background::Get()->displayTerrain(renderer);
    
    for( SpriteType type = SpriteType(TERRAIN+1); type< SpriteType(SPRITE_TYPE_SIZE); type =SpriteType(type+1) )
        displaySprites(renderer, type);
}

void SpritesHolder::CleanUp(void){
    SpritesHolder::~SpritesHolder();
}

using namespace rapidjson;

void    SpritesHolder::Load (const std::string& cataloge/*,SDL_Renderer* _renderer*/){
    std::string line, text;
    
    static  std::string  dataFilePath = SRC_PATH + string(cataloge);
    
    std::ifstream file(dataFilePath);
	if (!file.is_open()){
		cout << dataFilePath << endl;
		cout << "ERROR:data.json does not opened" << endl;
		assert(0);
	}
	
    while(std::getline(file, line))
    {
        text += line + "\n";
    }
    const char* data = text.c_str();
	
    
    Document document;
    document.Parse(data);
    assert(document.IsObject());
    assert(document["Sprites"].IsArray());
    //assert(document["Sprites"][1].IsObject());
    const Value& sprites = document["Sprites"];
    for (rapidjson::SizeType i = 0; i < sprites.Size(); i++)
    {
        const Value& sprite = sprites[i];
        //id
        std::string id = sprite["id"].GetString();
        unsigned frameNo = (unsigned) sprite["frameNo"].GetInt();
        SDL_Rect destRect;
        const Value& rect = sprite["destRect"];
        destRect.x = rect[0].GetInt();
        destRect.y = rect[1].GetInt();
        destRect.w = rect[2].GetInt();
        destRect.h = rect[3].GetInt();
        SDL_Point point;
        const Value& p = sprite["point"];
        point.x = p[0].GetInt();
        point.y = p[1].GetInt();
        
        bool isVisible = sprite["visible"].GetBool();
        SpriteType spriteType;
        int st = sprite["spriteType"].GetInt();
        switch(st){
            case 0:
                spriteType = SpriteType::MAIN_MENU_SINGLEPLAYER;
                break;
            case 1:
                spriteType = SpriteType::MAIN_MENU_MULTIPLAYER;
                break;
            case 2:
                spriteType = SpriteType::TERRAIN;
                break;
            case 3:
                spriteType = SpriteType::SUPER_ACE;
                break;
            case 4:
                spriteType = SpriteType::ALIEN_SHIP;
                break;
            case 5:
                spriteType = SpriteType::BIG_ALIEN_SHIP;
                break;
            case 6:
                spriteType = SpriteType::POWER_UPS;
                break;
            case 7:
                spriteType = SpriteType::GAME_INFO;
                break;
            case 8:
                spriteType = SpriteType::UNDEFINED;
                break;
            default:
                assert(0);
        }
        
        AnimationFilm* animationFilm = AnimationFilmHolder::Get()->GetFilm(sprite["animFilmId"].GetString()) ;
        //std::cout<<"ID: "<<id<<std::endl<<"frameNo: "<<frameNo<<std::endl;
        
        assert(sprite.IsObject());
        assert(sprite["id"].IsString());
        assert(sprite["destRect"].IsArray());
        
        //add Sprite 2 Sprite Holder
        if(spriteType == SpriteType::SUPER_ACE)
            new SuperAce(id, frameNo, destRect, point, isVisible, spriteType,animationFilm);
        else
            new Sprite(id, frameNo, destRect, point, isVisible, spriteType,animationFilm);
    }

}

void SpritesHolder::checkSpritesForDelete(){
    
    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteType type = SUPER_ACE;
    SpriteList* sl = NULL;
    SpriteList::const_iterator it;
    SpriteList::const_iterator it2;

    for(type=SUPER_ACE; type <= GAME_INFO; type = SpriteType(type+1)){
        sl = h->getSprites(type);
        if(sl == nullptr){
            assert(0);
        }

        it=sl->begin();
        
        while(it!=sl->end()){
            it2 = it;
            it2++;
            if( (*it)->isOutOfWindow() || (*it)->getState() == SpriteState::IN_COLUSION ){
                (*it)->destroySprite();
            }
            it = it2;
        }
    }
}
