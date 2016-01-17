#ifndef collision_handler_hpp
#define collision_handler_hpp

class Sprite;

class CollisionHandler{
public:
    virtual void operator()(Sprite* caller, Sprite* arg) const = 0;
    virtual CollisionHandler* Clone(void) const = 0;
    virtual ~CollisionHandler(){};
};

#endif