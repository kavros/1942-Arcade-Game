#include "AnimationFilm.hpp"

//TODO Change Masked Blit to SLD Blit
void AnimationFilm::displayFrame(SDL_Renderer* renderer, const SDL_Point point, unsigned frameNo, SDL_Rect dstRect) const{

	SDL_RenderCopyEx(renderer, _texture, &(_boxes[frameNo]), &dstRect, _degrees, &point, SDL_FLIP_NONE);
}

unsigned AnimationFilm::getTotalFrames(void) const{
    return (unsigned)_boxes.size();
}

SDL_Texture* AnimationFilm::getTexture(void) const  {
    return _texture;
}

const std::string AnimationFilm::getId (void) const {
    return _id;
}

const SDL_Rect  AnimationFilm ::getFrameBox(unsigned frameNo) const{
    assert(_boxes.size() > frameNo);
    return _boxes[frameNo];
}

void AnimationFilm::setDegrees(int d){
    _degrees =d;
}
AnimationFilm::AnimationFilm(SDL_Texture* texture ,vector<SDL_Rect> boxes ,string id){
    _texture=texture;
    _boxes=boxes;
    _id=id;
    _degrees = 0;
}