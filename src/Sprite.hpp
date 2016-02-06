#ifndef Sprite_hpp
#define Sprite_hpp

#include "includes.h"
#include "AnimationFilm.hpp"
#include "LatelyDestroyable.h"
#include "CollisionChecker.hpp"

#define SPRITE_TYPE_SIZE 8
#define SPRITE_STATE_SIZE  
class Sprite;

typedef enum SpriteType {
    MAIN_MENU_SINGLEPLAYER = 0,
    MAIN_MENU_MULTIPLAYER = 1,
    TERRAIN = 2,
    SUPER_ACE = 3,
    ALIEN_SHIP = 4,
    POWER_UPS = 5,
    GAME_INFO = 6,
    UNDEFINED = 7 ,
	First_SpriteType = MAIN_MENU_SINGLEPLAYER,
	Last_SpriteType = UNDEFINED

}SpriteType;

typedef enum SpriteState {
    FLYING = 0,
    FIRING = 1,
	MANEUVER = 2,
	STARTING = 3,
    IN_COLUSION = 4,
	ENDING = 5 ,

	First_SpriteState = FLYING,
	Last_SpriteState = ENDING
}SpriteState;

class Sprite : public LatelyDestroyable{
    
public:
    
    class CollisionHandler{
    public:
        virtual void operator()(Sprite* caller, Sprite* arg) const = 0;
        virtual CollisionHandler* Clone(void) const = 0;
        virtual ~CollisionHandler(){};
    };
    
    struct fireHandler : public Sprite::CollisionHandler{
        void operator()(Sprite* bullet,Sprite* arg) const;
        fireHandler* Clone(void) const;
        ~fireHandler();
    };
    
    struct touchHandler : public Sprite::CollisionHandler{
        void operator()(Sprite* aircraft,Sprite* arg) const;
        touchHandler* Clone(void) const;
        ~touchHandler();
    };
    
    struct touchPowerUpHandler : public Sprite::CollisionHandler{
        void operator()(Sprite* powerUp,Sprite* arg) const;
        touchPowerUpHandler* Clone(void) const;
        ~touchPowerUpHandler();
    };
    
protected:
    
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
    
    using Attached = std::map<std::string, Sprite*>;
    Attached _attached;
    Sprite* _parent;
    std::string _name; //inspect this
    bool undefeatable;
    void moveAttached(int dx, int dy);
    
    ~Sprite();

    void clearHandlers(void);

public:
    //collision detection functions
    void addCollisionHandler(const CollisionHandler& h);
    
	//setters
	void setState(SpriteState);
    void setId(std::string);
    virtual void setFrame(unsigned  i) ;
    void setVisibility (bool v);
    void setDstRect(SDL_Rect dstRect);
    void setDstRectX(int x);
    void setDstRectY(int y);
    void setCurrFilm(AnimationFilm* currFilm);
    void setUndefeatable(bool flag);
    void setPoint(SDL_Point point);
    
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
    AnimationFilm* getCurrFilm(void) const;
    Sprite* getParent();
    bool isUndefeatable();
    SDL_Point getPoint();

	//constructors
    Sprite();
    Sprite(std::string id, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,bool _isVisible,SpriteType _type,AnimationFilm* _currFilm);
    
    //basic functionallity
    virtual void move (int dx, int dy);
    
    virtual void filterMotion(int* dx, int* dy) const;
    
    void attach(Sprite* s, const std::string& name);
    
    void detach(const std::string& name, bool forDestroy);
    
    Sprite* getAttached(const std::string& name) const;
    
    virtual void destroySprite(void);
    
    void display (SDL_Renderer* renderer);
    
    bool isOutOfWindow();
  
};

#endif