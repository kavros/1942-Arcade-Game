#include "AnimatorHolder.h"

AnimatorHolder* AnimatorHolder::_holder = 0;

void AnimatorHolder::Register(Animator* a) {
    AnimatorHolder::getAnimatorHolder()->_map[a->getId()] = a;
    AnimatorHolder::getAnimatorHolder()->_suspended.push_back(a);
}
void AnimatorHolder::cancel(Animator* a) {
    AnimatorHolder::getAnimatorHolder()->_suspended.remove(a);
}

AnimatorHolder* AnimatorHolder::getAnimatorHolder(){
    if (!_holder)
        _holder = new AnimatorHolder();
    return _holder;
}

void AnimatorHolder::cleanup(){
    _holder->~AnimatorHolder();
    _holder = NULL;
}

//marking state
void AnimatorHolder::markAsRunning(Animator* a)	{

    AnimatorHolder::getAnimatorHolder()->_suspended.remove(a);
    AnimatorHolder::getAnimatorHolder()->_running.push_back(a);
    
}
void AnimatorHolder::markAsSuspended(Animator* a){

    AnimatorHolder::getAnimatorHolder()->_running.remove(a);
    AnimatorHolder::getAnimatorHolder()->_suspended.push_back(a);
    
}

void AnimatorHolder::progress(timestamp_t currTime) {
    AnimatorHolder* h = AnimatorHolder::getAnimatorHolder();

	AnimatorList::iterator it = h->_running.begin();
    AnimatorList::iterator it2;
	while (it != h->_running.end()){
		it2 = it;
		it2++;
		(*it)->progress(currTime);
		it = it2;
	}

}

void AnimatorHolder::checkAnimatorsForDelete(void){
    AnimatorHolder* h = AnimatorHolder::getAnimatorHolder();

    AnimatorList::iterator it = h->_running.begin();
    AnimatorList::iterator it2;
    while (it != h->_running.end()){
        it2 = it;
        it2++;
        (*it)->checkAnimatorForDelete();
        it = it2;
    }
    
    it = h->_suspended.begin();
    while (it != h->_suspended.end()){
        it2 = it;
        it2++;
        (*it)->checkAnimatorForDelete();
        it = it2;
    }

    return;
}

unsigned long AnimatorHolder::getTotalRunning(){
    
    return AnimatorHolder::getAnimatorHolder()->_running.size();
}

unsigned long AnimatorHolder::getTotalSuspended(){
    return AnimatorHolder::getAnimatorHolder()->_suspended.size();
}


AnimatorHolder::AnimatorHolder(){
    AnimatorHolder::_running.clear();
    AnimatorHolder::_suspended.clear();
}

AnimatorHolder::~AnimatorHolder(){
    AnimatorHolder::_running.clear();
    AnimatorHolder::_suspended.clear();
}

Animator* AnimatorHolder::getAnimator(animid_t id){
    return _holder->_map[id];
}

void AnimatorHolder::triggerBullets(){
    
    SpritesHolder* h = SpritesHolder::getSpritesHolder();
    SpriteList * sl = h->getSprites(ALIEN_SHIP);

    SpriteList::const_iterator it = sl->begin();

    while (it != sl->end()){
        if( (*it) && (*it)->getVisibility() && (*it)->isAlive() && !(*it)->isOutOfWindow() && (*it)->getState()!=IN_COLUSION ){
            ((EnemyFighter*)(*it))->fire();
            break;
        }
        it++;
    }

}

void AnimatorHolder::createExplosion(SDL_Rect dstRect){
    
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("explosion");
    assert(fireAnimationFilm);
    
    Sprite* explosion = new Sprite("explosionSprite", 0, dstRect, {0,0}, true, POWER_UPS, fireAnimationFilm);
    assert(explosion);
    
    SoundHolder::playSound("explosion");
    
    Animation* explosionAnimation = AnimationHolder::getAnimationHolder()->getAnimation("explosion");
    assert(explosionAnimation);
    
    MovingPathAnimator* explosionAnimator = new MovingPathAnimator("animatorExplosion", explosion, (MovingPathAnimation*)explosionAnimation);
    
    AnimatorHolder::Register(explosionAnimator);
    
    explosionAnimator->start(Game::getGameTime());
    
}

void AnimatorHolder::wakeUpAnimators(timestamp_t currTime){
	AnimatorHolder* h = AnimatorHolder::getAnimatorHolder();
	AnimatorList::iterator it = h->_suspended.begin();
	AnimatorList::iterator it2;

	
	it = h->_suspended.begin();
	while (it != h->_suspended.end()){
		it2 = it;
		it2++;
		if ((*it)->getState() == ANIMATOR_PAUSED ){
			timestamp_t offset = (currTime - (*it)->getLastTime());
			(*it)->timeShift(offset);

			//if Animator is for SuperAce dont put it in Running list
			//because it will never move again!!(BUG ?)
			if ((*it)->getId().find("SuperAce") != string::npos ){

			}else{

				(*it)->setState(ANIMATOR_RUNNING);
			}
			AnimatorHolder::markAsRunning(*it);
		}
		it = it2;
	}
}

void AnimatorHolder::pauseAnimators(){
	AnimatorHolder* h = AnimatorHolder::getAnimatorHolder();
	AnimatorList::iterator it = h->_running.begin();
	AnimatorList::iterator it2;

	//set all running animators as paused
	it = h->_running.begin();
	while (it != h->_running.end()){
		it2 = it;
		it2++;
		(*it)->setState(ANIMATOR_PAUSED);		
		AnimatorHolder::markAsSuspended(*it);
		it = it2;
	}
}

void triggerSuperAceMovingPathAnimator(){
    MovingPathAnimator* movingSuperAce = (MovingPathAnimator*) AnimatorHolder::getAnimator("SuperAceMovingAnimator");
    movingSuperAce->start(Game::getGameTime());
}

void triggerRedPlaneAnimator(){
    
    static int nameId=0;
    string name = "RedJet" + std::to_string(nameId);
    nameId++;

    AnimationFilm* animationFilm  = AnimationFilmHolder::Get()->GetFilm("red_plane");
    assert(animationFilm);
    
    Sprite* sprite = SpritesHolder::getSpritesHolder()->getSprite(SpriteType::ALIEN_SHIP, name);
    assert(sprite);
    Animation* animation = AnimationHolder::getAnimationHolder()->getAnimation("circle_250_250_30");
    assert(animation);

    MovingPathAnimator* animator = new MovingPathAnimator(name, sprite, (MovingPathAnimation*)animation);
    assert(animator);
    
    AnimatorHolder::Register(animator);
    
    animator->start(Game::getGameTime());

}

void triggerGreenPlaneAnimator(){
    
    static int nameId=0;
    string name = "GreenJet" + std::to_string(nameId);
    nameId++;
    
    AnimationFilm* animationFilm  = AnimationFilmHolder::Get()->GetFilm("green_jet");
    assert(animationFilm);
    
    Sprite* sprite = SpritesHolder::getSpritesHolder()->getSprite(SpriteType::ALIEN_SHIP, name);
    assert(sprite);
    
    Animation* animation = AnimationHolder::getAnimationHolder()->getAnimation("circle_250_250_30");
    assert(animation);
    
    MovingPathAnimator* animator = new MovingPathAnimator(name, sprite, (MovingPathAnimation*)animation);
    assert(animator);
    
    AnimatorHolder::Register(animator);
    
    animator->start(Game::getGameTime());
    
}

void triggerGreenDoubleEnginePlaneAnimator(){
    
    static int nameId=0;
    string name = "GreenDoubleEngineJet" + std::to_string(nameId);
    nameId++;
    
    AnimationFilm* animationFilm  = AnimationFilmHolder::Get()->GetFilm("green_double_engine");
    assert(animationFilm);
    
    Sprite* sprite = SpritesHolder::getSpritesHolder()->getSprite(SpriteType::ALIEN_SHIP, name);
    assert(sprite);
    
    Animation* animation = AnimationHolder::getAnimationHolder()->getAnimation("circle_250_250_30");
    assert(animation);
    
    MovingPathAnimator* animator = new MovingPathAnimator(name, sprite, (MovingPathAnimation*)animation);
    assert(animator);
    
    AnimatorHolder::Register(animator);
    
    animator->start(Game::getGameTime());
    
}

void triggerEndOfTheStageAnimator(){

	

	/*MovingPathAnimator* superAceEndingAnimator =
		(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceEndingAnimator");
	assert(superAceEndingAnimator);*/


	//superAceEndingAnimator->start(Game::getGameTime());

	/*SpriteStringHolder::getSpriteString("shootingString")->setVisibility(true);
	SpriteStringHolder::getSpriteString("downString")->setVisibility(true);
	SpriteStringHolder::getSpriteString("shootingDownPercent")->setVisibility(true);
	SpriteStringHolder::getSpriteString("endingBonusString")->setVisibility(true);
	SpriteStringHolder::getSpriteString("pointsString")->setVisibility(true);
	SpriteStringHolder::getSpriteString("points")->setVisibility(true);
	SpriteStringHolder::getSpriteString("letterR")->setVisibility(true);
	SpriteStringHolder::getSpriteString("1000Points")->setVisibility(true);
	SpriteStringHolder::getSpriteString("letterR")->setVisibility(true);
	*/
}
void AnimatorHolder::startTimeTickAnimators(){
    
    TimerTickAnimator::startTimeTickAnimator("superAceMovingPathTickAnimation", triggerSuperAceMovingPathAnimator );
    TimerTickAnimator::startTimeTickAnimator("enemyBulletsTickAnimation", AnimatorHolder::triggerBullets);
    TimerTickAnimator::startTimeTickAnimator("redPlaneTickAnimation", triggerRedPlaneAnimator );
    TimerTickAnimator::startTimeTickAnimator("greenPlaneTickAnimation", triggerGreenPlaneAnimator );
    TimerTickAnimator::startTimeTickAnimator("greenDoubleEnginePlaneTickAnimation", triggerGreenDoubleEnginePlaneAnimator );
	//TimerTickAnimator::startTimeTickAnimator("endOfTheStageTickAnimation", triggerEndOfTheStageAnimator);
}

using namespace rapidjson;

void    AnimatorHolder::Load (const std::string& cataloge){
    std::string line, text;
    
    static  std::string  dataFilePath = SRC_PATH + string(cataloge);
    
    std::ifstream file(dataFilePath);
    if (!file.is_open()){
        cout << dataFilePath << endl;
        cout << "ERROR:data.json does not opened" << endl;
        assert(0);
    }
    
    while(std::getline(file, line))
    {
        text += line + "\n";
    }
    const char* data = text.c_str();
    
    
    Document document;
    document.Parse(data);
    assert(document.IsObject());
    assert(document["MovingPathAnimators"].IsArray());
    //assert(document["Sprites"][1].IsObject());
    const Value& mpas= document["MovingPathAnimators"];
    for (rapidjson::SizeType i = 0; i < mpas.Size(); i++)
    {
        const Value& mpa = mpas[i];
        //id
        std::string id = mpa["id"].GetString();
        std::string animationId = mpa["animationId"].GetString();
        std::string spriteId = mpa["spriteId"].GetString();
        int st = mpa["spriteType"].GetInt();
        SpriteType spriteType = SpriteType(st);
        assert( st < SPRITE_TYPE_SIZE );
        
        Sprite* sprite= SpritesHolder::getSpritesHolder()->getSprite(spriteType, spriteId);
        MovingPathAnimation* animation = (MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation(animationId);
        MovingPathAnimator* animator  =	new MovingPathAnimator( id, sprite, animation);
        AnimatorHolder::Register(animator);
    }
    
}






