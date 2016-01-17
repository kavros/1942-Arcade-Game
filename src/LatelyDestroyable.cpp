#include "LatelyDestroyable.h"

std::list<LatelyDestroyable*> DestructionManager::_dead;

void LatelyDestroyable::Delete::operator()(LatelyDestroyable* o) const
{
	o->inDestruction = true; delete o;
}

void LatelyDestroyable::setAlive(bool a){
    alive = a;
}


//DestructionManager functions

void DestructionManager::Register(LatelyDestroyable* o) {
	assert(!o->isAlive());
	_dead.push_back(o);
}
void DestructionManager::commit(void) {
	std::for_each(		
		_dead.begin(),
		_dead.end(),
		LatelyDestroyable::Delete()
    );
	_dead.clear();
}

void DestructionManager::printDestructionManager(){

    //cannot see sprite
    
    if( _dead.empty() ){
        //cout<< "empty"<<endl;
    }
    else{
        cout<< _dead.size()<<endl;
    }
    /*
    for (std::list<LatelyDestroyable*>::iterator it=_dead.begin(); it != _dead.end(); ++it){
        
        //cout << ((Sprite*)(*it))->getId();
        //cout << (Sprite*)(*it)->getId();

    }
    */
}


