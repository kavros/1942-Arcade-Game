#ifndef AnimationFilm_hpp
#define AnimationFilm_hpp

#include "includes.h"

using namespace std;

class AnimationFilm{
  
protected:
    vector<SDL_Rect> _boxes;
    string  _id;
    SDL_Texture* _texture;

public:

    //accessors
	unsigned getTotalFrames (void) const;
	SDL_Texture* getTexture(void) const;
    const std::string getId (void) const;
    const SDL_Rect getFrameBox (unsigned frameNo) const;

    //renderer
	void  displayFrame(SDL_Renderer* renderer, const SDL_Point point, unsigned frameNo, SDL_Rect dstRect) const;

	//constuctor
	AnimationFilm(SDL_Texture* _texture ,vector<SDL_Rect> _boxes ,string _id);
}; 

#endif