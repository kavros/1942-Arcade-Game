#ifndef Sprite_hpp
#define Sprite_hpp

#include "includes.h"
#include "AnimationFilm.hpp"
#include "LatelyDestroyable.h"
#include "CollisionChecker.hpp"

#define SPRITE_TYPE_SIZE 8

class Sprite;

typedef enum SpriteType {
    MAIN_MENU_SINGLEPLAYER = 0,
    MAIN_MENU_MULTIPLAYER,
    TERRAIN,
    SUPER_ACE,
    ALIEN_SHIP,
    BIG_ALIEN_SHIP,
    POWER_UPS,
    GAME_INFO,
    UNDEFINED
}SpriteType;

typedef enum SpriteState {
    FLYING = 0,
    FIRING,
	MANEUVER
}SpriteState;

class Sprite : public LatelyDestroyable{
    
protected:
    
    class CollisionHandler{
    public:
        virtual void operator()(Sprite* caller, Sprite* arg) const = 0;
        virtual CollisionHandler* Clone(void) const = 0;
        virtual ~CollisionHandler(){};
    };
    
    //collision detection variables
    typedef std::list<CollisionHandler*> Handlers;
    SpriteState _state;
    Handlers _handlers;
    void notifyCollision(Sprite* arg);
    
    std::string _spriteId;
    unsigned  _frameNo;
    SDL_Rect _dstRect;
	SDL_Rect _srcRect;
	SDL_Point  _point; //point on the screen
    bool _isVisible;
	SpriteType _type;
    AnimationFilm* _currFilm;
    //TileLayer* _myLayer;
    
    using Attached = std::map<std::string, Sprite*>;
    Attached _attached;
    Sprite* _parent;
    std::string _name;
    
    void moveAttached(int dx, int dy);
    
public:
    //collision detection functions
    void addCollisionHandler(const CollisionHandler& h);
    void clearHandlers(void);
    
	//setters
	void setState(SpriteState);
    void setId(std::string);
    void setFrame(unsigned  i);
    void setVisibility (bool v);
    void setDstRect(SDL_Rect dstRect);
    void setDstRectX(int x);
    void setDstRectY(int y);
    void setCurrFilm(AnimationFilm* currFilm);
    AnimationFilm* getCurrFilm(void) const;

    //getters
    std::string getId(void) const;
    unsigned  getFrame(void) const;
    SDL_Rect getDstRect(void) const;
	bool getVisibility (void) const;
    void collisionCheck (Sprite* s);
	SpriteType getType();
	SpriteState getState();
    void changeDstRectX(int dx);
    void changeDstRectY(int dy);

	//constructors
    Sprite();
    Sprite(std::string id, SDL_Rect dstRect,bool isVisible,SpriteType type,AnimationFilm* currFilm);
    Sprite(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm);

    ~Sprite();
    
    //basic functionallity
    virtual void move (int dx, int dy);
    
	virtual void filterMotion(int* dx, int* dy) const {
        /* default is unfiltered motion */
    };
    
    void attach(Sprite* s, const std::string& name);
    
    void detach(const std::string& name, bool destroy);
    
    Sprite* getAttached(const std::string& name) const;
    
    virtual void Destroy(void){
        // supports auto detach policy
       	LatelyDestroyable::destroy();
        if (_parent)	// is attached
            _parent->detach(_name, false);
    }

    void display (SDL_Renderer* renderer);
    
    bool isOutOfWindow();
    
};

#endif