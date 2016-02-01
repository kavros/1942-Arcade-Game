#include "AnimatorHolder.h"

void updateGrayPlaneAnimation(MovingPathAnimator* grayJetAnimator);
void updateGrayJetAnimation(MovingPathAnimator* grayJetAnimator);
AnimatorHolder* AnimatorHolder::_holder = 0;

void AnimatorHolder::Register(Animator* a) {
    assert(AnimatorHolder::getAnimatorHolder()->_map[a->getId()] == nullptr);
    
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

    SpriteList * sl = SpritesHolder::getSprites(ALIEN_SHIP);

    SpriteList::const_iterator it = sl->begin();

    while (it != sl->end()){
        if( (*it) && (*it)->getVisibility() && (*it)->isAlive() && !(*it)->isOutOfWindow() && (*it)->getState()!=IN_COLUSION
           && ((EnemyFighter*)(*it))->getEnemyFighterType() != BULLET){
            ((EnemyFighter*)(*it))->fire();
        }
        it++;
    }

}

void AnimatorHolder::createExplosion(SDL_Rect dstRect){
    
    static int nameId=0;
    string spriteExplosionId = "spriteExplosionId" + std::to_string(nameId);
    string animatorExplosionId = "animatorExplosionId" + std::to_string(nameId);
    nameId++;
    
    AnimationFilm* fireAnimationFilm = AnimationFilmHolder::Get()->GetFilm("explosion");
    assert(fireAnimationFilm);
    
    Sprite* explosion = new Sprite(spriteExplosionId, 0, dstRect, {0,0}, true, POWER_UPS, fireAnimationFilm);
    assert(explosion);
    
    SoundHolder::playSound("explosion");
    
    Animation* explosionAnimation = AnimationHolder::getAnimationHolder()->getAnimation("explosion");
    assert(explosionAnimation);
    
    MovingPathAnimator* explosionAnimator = new MovingPathAnimator(animatorExplosionId, explosion, (MovingPathAnimation*)explosionAnimation);
    assert(explosionAnimator);
    
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
    assert(movingSuperAce);
    movingSuperAce->start(Game::getGameTime());
}

void triggerRedPlaneAnimator(){
    
    static int nameId=0;
    string name = "RedJetAnimator" + std::to_string(nameId);
    nameId++;

    MovingPathAnimator* animator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());

}

void triggerGreenJetPlaneAnimator(){
    static int nameId=0;
    string name = "GreenJetAnimator" + std::to_string(nameId);
    nameId++;
    
    MovingPathAnimator* animator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());
}

void triggerGreenDoubleEnginePlaneAnimator(){
    static int nameId=0;
    string name = "GreenDoubleEngineJetAnimator" + std::to_string(nameId);
    nameId++;
    
    MovingPathAnimator* animator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());
}

void triggerEndOfTheStageAnimator(){

	

	MovingPathAnimator* superAceEndingAnimator =
		(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceEndingAnimator");
	assert(superAceEndingAnimator);
	superAceEndingAnimator->start(Game::getGameTime());
	cout << "triggerEndOfTheStageAnimator" << endl;
	//superAceEndingAnimator->start(Game::getGameTime());

	SpriteStringHolder::getSpriteString("shootingString")->setVisibility(true);
	SpriteStringHolder::getSpriteString("downString")->setVisibility(true);
	SpriteStringHolder::getSpriteString("shootingDownPercent")->setVisibility(true);
	SpriteStringHolder::getSpriteString("endingBonusString")->setVisibility(true);
	SpriteStringHolder::getSpriteString("pointsString")->setVisibility(true);
	SpriteStringHolder::getSpriteString("points")->setVisibility(true);
	SpriteStringHolder::getSpriteString("letterR")->setVisibility(true);
	SpriteStringHolder::getSpriteString("1000Points")->setVisibility(true);
	SpriteStringHolder::getSpriteString("letterR")->setVisibility(true);
	
	//Game::setState(END_OF_STAGE);
}

void triggerGrayPlaneAnimator(){
	static int nameId = 0;
	string name = "GrayPlaneAnimator" + std::to_string(nameId);
	nameId++;

	MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
	assert(animator);
    updateGrayPlaneAnimation(animator);
	animator->start(Game::getGameTime());

}

void triggerRedPlaneTickAnimations(){
    static int id = 0;
    string redPlaneTickAnimationId = "redPlaneTickAnimation" +  std::to_string(id);
    id++;
    
    TimerTickAnimator::startTimeTickAnimator(redPlaneTickAnimationId, triggerRedPlaneAnimator );
}
void triggerGrayJetTickAnimator(){
	static int nameId = 0;
	string name = "GrayJetAnimator" + std::to_string(nameId);
	nameId++;

	MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
	assert(animator);
	animator->start(Game::getGameTime());
}
void AnimatorHolder::startTimeTickAnimators(){
    
    TimerTickAnimator::startTimeTickAnimator("superAceMovingPathTickAnimation", triggerSuperAceMovingPathAnimator );
    TimerTickAnimator::startTimeTickAnimator("enemyBulletsTickAnimation", AnimatorHolder::triggerBullets);
    TimerTickAnimator::startTimeTickAnimator("greenPlaneTickAnimation", triggerGreenJetPlaneAnimator );
    TimerTickAnimator::startTimeTickAnimator("greenDoubleEnginePlaneTickAnimation", triggerGreenDoubleEnginePlaneAnimator );
	TimerTickAnimator::startTimeTickAnimator("grayPlaneTickAnimation", triggerGrayPlaneAnimator);

    TimerTickAnimator::startTimeTickAnimator("redPlaneTickAnimations", triggerRedPlaneTickAnimations );
	//TimerTickAnimator::startTimeTickAnimator("grayJetTickAnimation", triggerGrayJetTickAnimator);
}	

using namespace rapidjson;

void    AnimatorHolder::Load (const std::string& cataloge){
    std::string line, text;
    
    static  std::string  dataFilePath = SRC_PATH + string(cataloge);
    
    std::ifstream file(dataFilePath);
    if (!file.is_open()){
        cout << dataFilePath << endl;
        cout << "ERROR:animator.json does not opened" << endl;
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
        
        Sprite* sprite= SpritesHolder::getSprite(spriteType, spriteId);
        assert(sprite);
        MovingPathAnimation* animation = (MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation(animationId);
        assert(animation);
        MovingPathAnimator* animator  =	new MovingPathAnimator( id, sprite, animation);
        assert(animator);
    }
    
}
    
void AnimatorHolder::updateAllGrayPlaneAnimations(){
    
    MovingPathAnimator* grayPlaneAnimator;
    string grayPlaneAnimatorName, grayPlaneAnimationName;
    AnimatorHolder::AnimatorList::const_iterator it2 = getAnimatorHolder()->_running.end();
    AnimatorHolder::AnimatorList::const_iterator  it = getAnimatorHolder()->_running.begin();//_running.begin();
    
    while (it != getAnimatorHolder()->_running.end()){
        it2 = it;
        it2++;
        assert((*it));
        if ((*it)->getId().find("GrayPlaneAnimator") != std::string::npos ){
            grayPlaneAnimator= (MovingPathAnimator*) (*it);
            updateGrayPlaneAnimation(grayPlaneAnimator);
        }
        it = it2;
    }
    
}

void updateGrayPlaneAnimation(MovingPathAnimator* grayJetAnimator){
    
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
    
    MovingPathAnimation* grayJetAnimation = grayJetAnimator->getMovingPathAnimation();
    
    assert(grayJetAnimator);
    assert(grayJetAnimation);
    if (!grayJetAnimator->isAlive()){
        return;
    }
    
    
    
    if (grayJetAnimation->getPath().front()._dy < 0){
        return;
    }
    
    PathEntry path;
    //path._dx = 1;
    //path._dy = 0;
    path._frame = grayJetAnimation->getPath().front()._frame;
    path._delay = grayJetAnimation->getPath().front()._delay;
    path._visibility = true;
    
    
    
    int superAcePositionOnX = superAce->getDstRect().x;
    int grayJetPositionOnX = grayJetAnimator->getSprite()->getDstRect().x;
    
    
    int grayJetPositionOnY = grayJetAnimator->getSprite()->getDstRect().y;
    int SuperAcePositionOnY = superAce->getDstRect().y;
    
    
    
    
    if (grayJetPositionOnX > superAcePositionOnX){
        //an o superace einai pio aristera apo to gray kai
        //to gray kinite deksia h den kinitai tote vale to na pigenei aristera
        if (grayJetAnimation->getPath().front()._dx >= 0){
            path._dx = -5;
            path._dy = 5;
            std::list<PathEntry> p;
            p.push_front(path);
            grayJetAnimation->setPath(p);
        }
    }
    else if (grayJetPositionOnX < superAcePositionOnX){
        if (grayJetAnimation->getPath().front()._dx <= 0){
            path._dx = 5;
            path._dy = 5;
            std::list<PathEntry> p;
            p.push_front(path);
            grayJetAnimation->setPath(p);
        }
        
    }
    else {
        //do not move on x axis
        if (grayJetAnimation->getPath().front()._dx != 0){
            
            path._dx = 0;
            path._dy = 5;
            std::list<PathEntry> p;
            p.push_front(path);
            grayJetAnimation->setPath(p);
        }
    }
    
    
    if (grayJetPositionOnY > SuperAcePositionOnY - 100){
        
        //stop
        if (grayJetAnimation->getPath().front()._dy > 0){
            path._dy = -5;
            path._dx = -5;
            path._frame = 1;
            
            
            std::list<PathEntry> p;
            p.push_front(path);
            grayJetAnimation->setPath(p);
            
        }
    }
}


void  AnimatorHolder::updateAllGrayJetsAnimations(){
	updateGrayJetAnimation((MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator("GrayJetAnimator0"));
}
void  updateGrayJetAnimation(MovingPathAnimator* grayJetAnimator){
	assert(grayJetAnimator);

	if (!grayJetAnimator->isAlive()){
		return;
	}
	SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");

	MovingPathAnimation* grayJetAnimation = grayJetAnimator->getMovingPathAnimation();
	assert(grayJetAnimation);
	PathEntry path;
	//path._dx = 1;
	//path._dy = 0;
	path._frame = grayJetAnimation->getPath().front()._frame;
	path._delay = grayJetAnimation->getPath().front()._delay;
	path._visibility = true;

	int superAcePositionOnX = superAce->getDstRect().x;
	int grayJetPositionOnX = grayJetAnimator->getSprite()->getDstRect().x;


	int grayJetPositionOnY = grayJetAnimator->getSprite()->getDstRect().y;
	int SuperAcePositionOnY = superAce->getDstRect().y;

	if (grayJetPositionOnX > superAcePositionOnX){
		//an o superace einai pio aristera apo to gray kai
		//to gray kinite deksia h den kinitai tote vale to na pigenei aristera
		if (grayJetAnimation->getPath().front()._dx >= 0){

			grayJetAnimation->changeDxDy(-5, 5);

		}
	}
	else if (grayJetPositionOnX < superAcePositionOnX){
		if (grayJetAnimation->getPath().front()._dx <= 0){
			grayJetAnimation->changeDxDy(5, 5);

		}
		else {
			//do not move on x axis
			if (grayJetAnimation->getPath().front()._dx != 0){
				grayJetAnimation->changeDxDy(5, 0);
			}
		}



		if (grayJetPositionOnY > WIN_HEIGHT - 100){
			if (grayJetAnimation->getPath().front()._dy > 0){
				grayJetAnimation->changeDxDy(-17, 0);
				grayJetAnimator->getSprite()->getCurrFilm()->setDegrees(90);

			}
		}
		if (grayJetPositionOnX < 100){
			if (grayJetAnimation->getPath().front()._dx < 0){
				grayJetAnimation->changeDxDy(0, -17);
				grayJetAnimator->getSprite()->getCurrFilm()->setDegrees(180);

			}
		}
		if (grayJetPositionOnY < 100){
			if (grayJetAnimation->getPath().front()._dy < 0){
				grayJetAnimation->changeDxDy(17, 0);
				grayJetAnimator->getSprite()->getCurrFilm()->setDegrees(270);

			}
		}


	}
}

