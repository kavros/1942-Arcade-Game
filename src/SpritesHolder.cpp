
#include "SuperAce.h"
#include "EnemyFighter.hpp"
#include "SpritesHolder.hpp"

SDL_Rect getRandomDestRect(EnemyFighterType e,SDL_Rect dst);
SpritesHolder* SpritesHolder::_holder = 0;

SpritesHolder::SpritesHolder(){
    
    SpriteType type;
    
    for(type=SpriteType(0); type <= SpriteType(SPRITE_TYPE_SIZE); type = SpriteType(type+1)){
        _sprites[type] = new SpriteList();
    }

}

SpritesHolder::~SpritesHolder(){
    _holder->_sprites.clear();
    _holder = nullptr;
}

void SpritesHolder::add(Sprite *s){
    
    assert(s && s->getType()>=0 && s->getType()< SpriteType(SPRITE_TYPE_SIZE) );

    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* sl = h->getSprites(s->getType());
    
    assert(h && sl);

    if(s->getType() == ALIEN_SHIP ){
        ;
    }
    
    sl->push_back(s);
    ;
}

void SpritesHolder::remove(Sprite *s){
    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* sl = h->getSprites(s->getType());
    
    assert(h && sl);
    
    sl->remove(s);
}

Sprite* SpritesHolder::getSprite(SpriteType type, std::string id){

    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* sl = h->getSprites(type);
    
    assert(h && sl);
    
    for (std::list<Sprite*>::iterator it=sl->begin(); it != sl->end(); ++it){
        
        if((*it)->getId().compare(id) == 0)
            return *it;
    }
    cout<<"There is No Sprite with this id"<<std::endl;
    return nullptr;
}

void SpritesHolder::printSprites(SpriteType type){

    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* sl = h->getSprites(type);
    
    assert(h && sl);
    
    cout<<endl<<endl;
    for (std::list<Sprite*>::iterator it=sl->begin(); it != sl->end(); ++it){
        cout<<(*it)->getId()<<endl;
    }
    cout<<endl<<endl;
}

SpritesHolder* SpritesHolder::getSpritesHolder(){
    if (!_holder){
        _holder = new SpritesHolder();
    }
    return _holder;
}

SpriteList * SpritesHolder::getSprites(SpriteType type){
    assert(type>=0 && type<=SpriteType(SPRITE_TYPE_SIZE) );

    SpritesHolder* h = SpritesHolder::getSpritesHolder();

    SpriteByType::const_iterator i = h->_sprites.find(type);
    
    return i != h->_sprites.end() ? i->second : nullptr;
    
}

void SpritesHolder::displaySprites(SDL_Renderer* renderer, SpriteType type){
    assert(type>=0 && type<=SpriteType(SPRITE_TYPE_SIZE) );
    
    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* sl = h->getSprites(type);
    
    assert(h && sl);
    
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

void SpritesHolder::cleanUp(void){
    SpritesHolder::getSpritesHolder()->~SpritesHolder();
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
    for (rapidjson::SizeType i = 0; i < sprites.Size(); i++){
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

        spriteType = SpriteType(st);
        assert( st < SPRITE_TYPE_SIZE );

        AnimationFilm* animationFilm = AnimationFilmHolder::Get()->GetFilm(sprite["animFilmId"].GetString()) ;
        
        assert(sprite.IsObject());
        assert(sprite["id"].IsString());
        assert(sprite["destRect"].IsArray());
        
        int repetition = sprite["repetition"].GetInt();
        std::string id2;
        for(int k = 0; k < repetition; ++k){
            id2 = id + std::to_string(k);
            //add Sprite 2 Sprite Holder
            if(spriteType == SpriteType::SUPER_ACE){
                new SuperAce(id2, frameNo, destRect, point, isVisible, spriteType,animationFilm);
            }
            else if(spriteType == SpriteType::ALIEN_SHIP){
                int remainingBullets = sprite["remainingBullets"].GetInt();
                assert(sprite["enemyType"].IsInt());
                enum EnemyFighterType e = EnemyFighterType(sprite["enemyType"].GetInt());
                
                destRect = getRandomDestRect(e,destRect);
                new EnemyFighter(id2, frameNo, destRect, point, isVisible, spriteType,animationFilm,e,remainingBullets);
                
            }else if(spriteType == SpriteType::TERRAIN && id2.compare("backgroundSprite0")==0 ){
                Background::Get(id2, frameNo, destRect, point, isVisible, spriteType,animationFilm);
            }else{
                new Sprite(id2, frameNo, destRect, point, isVisible, spriteType,animationFilm);
            }
            
        }
    }
    
}


SDL_Rect getRandomDestRect(EnemyFighterType e,SDL_Rect dst){
    switch (e) {
        case EnemyFighterType(3):{
            //dst.x = 0;
            dst.y = rand() % 384 + 92; // random between 92 - 476
            break;}
        case EnemyFighterType(5):{
            //dst.x = 0;
            dst.y = rand() % 384 + 92; // random between 92 - 476
            break;}
        default:break;
    }
    return dst;
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
            if( ((*it)->isOutOfWindow() || (*it)->getState() == SpriteState::IN_COLUSION) && ((*it)->getId().compare("SuperAce0") != 0) ){
                (*it)->destroySprite();
            }
            it = it2;
        }
    }
}

bool SpritesHolder::uniqueAliveFromTeam(Sprite* sprite){
    
    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList* st = h->getSprites(sprite->getType(  ));
   
    
    
    
    
        
    int enemyId,groupId = 0;
    std::size_t found;
    std::string bonusId = sprite->getId();
    std::string s = "RedJetRight";
    std::string g = "RedJetLeft";
    std::string* last;
    found = bonusId.find(s);
    if (found == 0){
        bonusId.erase(found, s.length());
        groupId = std::stoi( bonusId )/5;
        last = &s;
    }else {
        found = bonusId.find(g);
        if (found == 0){
            bonusId.erase(found, g.length());
            groupId = std::stoi( bonusId )/5;
            last = &g;
        }else {
            
            assert(0);
        }
    }
    
    if( sprite->getType() == ALIEN_SHIP ){
        
        SpriteList::const_iterator it = st->begin();
        EnemyFighter* enemyFighter = (EnemyFighter*)sprite;
        
        if( enemyFighter->getEnemyFighterType() == RED_PLANE ){
            
            while(it != st->end()){
                enemyFighter = (EnemyFighter*)(*it);
                
                if( enemyFighter->getEnemyFighterType() == RED_PLANE &&  enemyFighter!=sprite ){
                    bonusId = enemyFighter->getId();
                    found = bonusId.find(*last);
                    if (found == 0){
                        bonusId.erase(found, (*last).length());
                        enemyId = std::stoi( bonusId );
                        if( enemyFighter->isAlive() && /*enemyFighter->getVisibility() &&*/ (enemyId >= groupId*5) && (enemyId < (groupId+1)*5) ){
                            return false;
                        }
                    }
                    /*if( enemyFighter->isAlive() && enemyFighter->getVisibility() && (enemyId >= groupId*5) && (enemyId < (groupId+1)*5) ){
                        return false;
                    }*/
                }
                
                ++it;
            }
            
        }
        
    }
    return true;
}


void SpritesHolder::smallAndBigEnemyFireEnable(){
    
    SpriteList* sl = SpritesHolder::getSprites(ALIEN_SHIP);
    SpriteList::const_iterator it = sl->begin();
    EnemyFighter* enemyFighter;
    
    while ( it != sl->end() ){
        enemyFighter = (EnemyFighter*)(*it);
        if( enemyFighter->getEnemyFighterType() != EnemyFighterType(BIG_GREEN) &&
           enemyFighter->getEnemyFighterType() != EnemyFighterType(BIG_GREY)){
            
            enemyFighter->setEnemyFireEnable(true);
            
        }
        ++it;
    }

}
