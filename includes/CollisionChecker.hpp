#ifndef Collision_checker_hpp
#define Collision_checker_hpp

#include "../includes/includes.h"

class Sprite;

//Singleton class
class CollisionChecker {
    
private:
    
    typedef std::pair<Sprite*, Sprite*> Pair;
    typedef std::list<Pair> PairList;
    
    struct checkFunctor {
        void operator()(const Pair& p) const;
    };
    
    PairList pairs;
    
    static CollisionChecker* _holder;
    
    CollisionChecker();
    ~CollisionChecker();
    
public:
    
    static CollisionChecker* getCollsionCheckerHolder();
    
    static void Register(Sprite* s1, Sprite* s2);
    static void CancelAll(Sprite* s);

    static void Check (void);
    
};

#endif