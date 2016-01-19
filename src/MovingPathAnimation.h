#ifndef moving_path_animation_h
#define moving_path_animation_h

#include "Animation.h"
#include <list>



 struct PathEntry{
	typedef unsigned frame_t;
	offset_t				_dx, _dy;
	frame_t					_frame;
	delay_t					_delay;
     bool                   _visibility;

	PathEntry(void) :_dx(0), _frame(0), _delay(0), _visibility(true){}

	PathEntry(const PathEntry* p) :_dx(p->_dx), _dy(p->_dy),
		_frame(p->_frame), _visibility(p->_visibility), _delay(p->_delay){}
};


class MovingPathAnimation : public Animation{
public:
	const std::list<PathEntry>& getPath(void) const{
		return _path;
	}
	void setPath(const std::list<PathEntry>& p){
		_path.clear();
		_path = p;
	}
    bool getContinuous(void) const { return _continuous; }
    void setContinuous(bool c) { _continuous = c; }
	Animation* clone(animid_t newId) const {
		return new MovingPathAnimation(_path, newId,_continuous);
	}
	MovingPathAnimation(const std::list<PathEntry>& path, animid_t id,bool continuous) :
		_path(path), Animation(id), _continuous(continuous){}

private:
	typedef std::list<PathEntry> PathsList;
	std::list<PathEntry> _path;
    bool _visibility;
    bool _continuous;

};

#endif