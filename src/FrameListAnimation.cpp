#include "FrameListAnimation.h"


const std::list<frame_t>& FrameListAnimation::GetFrames(void) const {
	return frames;
}
void FrameListAnimation::SetFrames(const std::list<frame_t>& f)
{
	frames.clear(); frames = f;
}
	

Animation* FrameListAnimation::Clone(animid_t newId) const {
    return NULL;
}

FrameListAnimation::FrameListAnimation(
	const std::list<frame_t>& _frames,
	offset_t dx,
	offset_t dy,
	delay_t d,
	bool c,
	animid_t id
	) : frames(_frames), MovingAnimation(dx, dy, d, c, id){}
