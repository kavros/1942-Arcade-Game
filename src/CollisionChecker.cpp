#include "CollisionChecker.hpp"
#include "Sprite.hpp"

CollisionChecker* CollisionChecker::_holder = 0;

CollisionChecker::CollisionChecker(){
  //  pairs = new PairList();
}

CollisionChecker::~CollisionChecker(){
    pairs.clear();
}

CollisionChecker* CollisionChecker::getCollsionCheckerHolder(){
    if(!_holder){
        _holder = new CollisionChecker();
    }
    return _holder;
}

void CollisionChecker::Register(Sprite* s1, Sprite* s2){
    assert(s1->isAlive());
    assert(s2->isAlive());
    
    CollisionChecker* h = CollisionChecker::getCollsionCheckerHolder();

    h->pairs.push_back(Pair(s1,s2));
    
}

void CollisionChecker::Cancel(Sprite* s1, Sprite* s2){
    CollisionChecker* holder = CollisionChecker::getCollsionCheckerHolder();
    PairList::const_iterator it = holder->pairs.begin();
    PairList::const_iterator it2;
    static int j = 0;
    if(!holder->pairs.empty())
        while (it != holder->pairs.end()){
            it2=it;
            it2++;
            if( (*it).first == s1 && (*it).second == s2){
                cout<<"j : "<<j++<<" pairs on holder:"<<holder->pairs.size()<<std::endl;
                holder->pairs.erase(it);
            }
            it=it2;
        }
}

void CollisionChecker::Check (void){
    CollisionChecker* holder = CollisionChecker::getCollsionCheckerHolder();
    std::for_each(  holder->pairs.begin(), holder->pairs.end(), checkFunctor()  );
}

void CollisionChecker::CancelAll(Sprite* s){
    assert(s->isAlive());
    
    CollisionChecker* holder = CollisionChecker::getCollsionCheckerHolder();
    PairList::const_iterator it = holder->pairs.begin();
    PairList::const_iterator it2;

    if(!holder->pairs.empty())
        while (it != holder->pairs.end()){
            it2=it;
            it2++;
            if( (*it).first == s){
                assert((*it).second->isAlive());
                CollisionChecker::Cancel(s, (*it).second);
            }
            it=it2;
        }
}
//setAlive
void CollisionChecker::checkFunctor::operator()(const Pair& p) const {
    Sprite* s1=p.first;
    Sprite* s2=p.second;
    
    if(s1 && s2)
        if(s1->isAlive() && s2->isAlive()){
        
            assert(s1->isAlive());
            assert(s2->isAlive());
            
            if( s1->getVisibility() && s2->getVisibility() ){
                s1->collisionCheck(s2);
            }
            
        }
}
