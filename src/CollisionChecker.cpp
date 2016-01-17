#include "CollisionChecker.hpp"

CollisionChecker* CollisionChecker::holder = 0;

CollisionChecker::CollisionChecker(){
}

CollisionChecker::~CollisionChecker(){
    pairs.clear();
}

CollisionChecker* CollisionChecker::getCollsionCheckerHolder(){
    if(!holder){
        holder = new CollisionChecker();
    }
    return holder;
}

//typedef std::pair<Sprite*, Sprite*> Pair;
//typedef std::list<Pair*> PairList;

void CollisionChecker::Register(Sprite* s1, Sprite* s2){
    Pair* p = new Pair(s1,s2);
    pairs.push_back(p);
    
}

void CollisionChecker::Cancel(Sprite* s1, Sprite* s2){
    Pair* p = new Pair(s1,s2);
    pairs.remove(p);
}

void CollisionChecker::Check(void){
    CollisionChecker* holder = CollisionChecker::getCollsionCheckerHolder();
    std::for_each(  holder->pairs.begin(), holder->pairs.end(), CheckFunctor()  );
}


