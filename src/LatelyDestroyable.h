#ifndef LATELYDESTROYABLE_H
#define LATELYDESTROYABLE_H

#include "includes.h"

class LatelyDestroyable;

class DestructionManager {
private:
	static std::list<LatelyDestroyable*> _dead;
public:
	static void Register(LatelyDestroyable* o);
	static void commit(void);
    static void printDestructionManager();
};

class LatelyDestroyable {
protected:
	friend class DestructionManager;
	bool alive;
	bool inDestruction;
	virtual ~LatelyDestroyable() { assert(inDestruction); }
    
	class Delete : public std::unary_function<LatelyDestroyable*, void>
	{
		public: void operator()(LatelyDestroyable* o) const;
	};
	friend class Delete;
	
public:
	bool isAlive(void) const { return alive; }
	void destroy(void) {
		if (alive) {
			alive = false;
			DestructionManager::Register(this);
        }else{
            assert(0);
        }
	}
	void operator()(LatelyDestroyable* o) const;
    void setAlive(bool a);
	//virtual LatelyDestroyable(void) : alive(true), inDestruction(false){}
};
#endif