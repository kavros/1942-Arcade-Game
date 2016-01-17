#ifndef Collision_checker_hpp
#define Collision_checker_hpp

#include "includes.h"
#include "Sprite.hpp"



//Singleton class
class CollisionChecker {
    
private:
    
    typedef std::pair<Sprite*, Sprite*> Pair;
    typedef std::list<Pair*> PairList;
    
    PairList pairs;
    
    struct CheckFunctor : public std::unary_function<Pair, void> {
        void operator()(const Pair& p) const { p.first->collisionCheck(p.second); }
    };

    static CollisionChecker* holder;
    
    CollisionChecker();
    ~CollisionChecker();
    
public:

    static CollisionChecker* getCollsionCheckerHolder();
    
    void Register(Sprite* s1, Sprite* s2);
    void Cancel (Sprite* s1, Sprite* s2);
    static void Check (void);
  
};

#endif