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

    holder->pairs->remove(new Pair(s1,s2));
}

void CollisionChecker::Check (void){
    CollisionChecker* holder = CollisionChecker::getCollsionCheckerHolder();
    //std::for_each(  holder->pairs.begin(), holder->pairs.end(), CheckFunctor()  );
    Sprite* s1=nullptr;
    Sprite* s2=nullptr;
    PairList::const_iterator it = holder->pairs->begin();
    
    while(it != holder->pairs->end()){
        s1 = (*it)->first;
        s2 = (*it)->second;

        if( s1->isAlive() && s2->isAlive()  ){
            s1->collisionCheck(s2);
        }
    
        it++;
    }
}

void CollisionChecker::CancelAll(Sprite* s){
    CollisionChecker* holder = CollisionChecker::getCollsionCheckerHolder();
    PairList::const_iterator it = holder->pairs->begin();
    PairList::const_iterator it2;

    if(!holder->pairs->empty())
        while (it != holder->pairs->end()){
            it2=it;
            it2++;
            if( (*it)->first == s){
                CollisionChecker::Cancel(s, (*it)->second);
            }
            it=it2;
        }
}

