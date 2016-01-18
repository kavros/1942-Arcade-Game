#include "CollisionChecker.hpp"

CollisionChecker* CollisionChecker::holder = 0;

CollisionChecker::CollisionChecker(){
    pairs = new PairList();
}

CollisionChecker::~CollisionChecker(){
    pairs->clear();
}

CollisionChecker* CollisionChecker::getCollsionCheckerHolder(){
    if(!holder){
        holder = new CollisionChecker();
    }
    return holder;
}

void CollisionChecker::Register(Sprite* s1, Sprite* s2){
    CollisionChecker* holder = CollisionChecker::getCollsionCheckerHolder();

    Pair* p = new Pair(s1,s2);
    holder->pairs->push_back(p);
    
}

void CollisionChecker::Cancel(Sprite* s1, Sprite* s2){
    CollisionChecker* holder = CollisionChecker::getCollsionCheckerHolder();

    Pair* p = new Pair(s1,s2);
    holder->pairs->remove(p);
}

void CollisionChecker::Check (void){
    CollisionChecker* holder = CollisionChecker::getCollsionCheckerHolder();
    //std::for_each(  holder->pairs.begin(), holder->pairs.end(), CheckFunctor()  );
    
    if(!holder->pairs->empty())
        for (PairList::iterator it = holder->pairs->begin(); it != holder->pairs->end(); ++it){
            ((*it)->first)->collisionCheck((*it)->second);
        }
    
}


