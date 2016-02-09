 #include "AnimatorHolder.h"

void updateGreyPlaneAnimation(MovingPathAnimator* grayJetAnimator);
void updateGreyJetAnimation(MovingPathAnimator* grayJetAnimator);
void triggerMediumGreenPlaneAnimator();

void  updateGreenJetAnimation(MovingPathAnimator* grayJetAnimator);

AnimatorHolder* AnimatorHolder::_holder = 0;
bool AnimatorHolder::movingEnable = false;

void AnimatorHolder::Register(Animator* a) {
    assert(AnimatorHolder::getAnimatorHolder()->_map[a->getId()] == nullptr);
    
    AnimatorHolder::getAnimatorHolder()->_map[a->getId()] = a;
    AnimatorHolder::getAnimatorHolder()->_suspended.push_back(a);
}
void AnimatorHolder::cancel(Animator* a) {
    AnimatorHolder::getAnimatorHolder()->_suspended.remove(a);
    AnimatorHolder::getAnimatorHolder()->_running.remove(a);
    
    AnimatorMap::const_iterator it = AnimatorHolder::getAnimatorHolder()->_map.begin();
    AnimatorMap::const_iterator it2;
    
    if(!AnimatorHolder::getAnimatorHolder()->_map.empty())
        while (it != AnimatorHolder::getAnimatorHolder()->_map.end()){
            it2=it;
            it2++;
            if( ((string)(*it).first).compare(a->getId())==0 ){
                AnimatorHolder::getAnimatorHolder()->_map.erase(it);
            }
            
            it=it2;
            
            
        }
    
    //AnimatorHolder::getAnimatorHolder()->_map[a->getId()] = nullptr;
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
        if((*it)->isAlive())
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

    /*
    AnimatorMap::const_iterator itt = h->_map.begin();
    AnimatorMap::const_iterator itt2;
    
    while (itt != h->_map.end()){
        itt2=itt;
        itt2++;
        
        if(((*itt).second)){
            ((*itt).second)->checkAnimatorForDelete();
        }
        
       itt=itt2;
        
    }
    */
    
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
    
    SDL_Rect rect = { dstRect.x+dstRect.w/2 , dstRect.y+dstRect.h/2 , 20 , 20 };
    
    Sprite* explosion = new Sprite(spriteExplosionId, 0, rect , {0,0}, true, POWER_UPS, fireAnimationFilm);
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
			if ((*it)->getId().find("SuperAce0") != string::npos ){

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

void triggerRedJetRightAnimator(){
    
    static int nameId=0;
    string name = "RedJetRightAnimator" + std::to_string(nameId);
    nameId++;

    MovingPathAnimator* animator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());

}

void triggerRedJetLeftAnimator(){
    
    static int nameId=0;
    string name = "RedJetLeftAnimator" + std::to_string(nameId);
    nameId++;
    
    MovingPathAnimator* animator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());
    
}

void triggerMiniGreenJetAnimator(){
    static int nameId=0;
    string name;
    if(nameId % 2 == 0){
        name = "MiniGreenJetLeftAnimator" + std::to_string(nameId/2);
    }else{
        name = "MiniGreenJetRightAnimator" + std::to_string(nameId/2);
    }
    nameId++;
    
    MovingPathAnimator* animator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());
}

void triggerMiniGreenDoubleEngAnimator(){
    static int nameId=0;
    string name ;
    if(nameId % 2 == 0){
        name = "MiniGreenDoubleEngRightAnimator" + std::to_string(nameId/2);
    }else{
        name = "MiniGreenDoubleEngLeftAnimator" + std::to_string(nameId/2);
    }
    nameId++;
    
    MovingPathAnimator* animator = (MovingPathAnimator*) AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());
}


void triggerMiniGreyOneEngAnimator(){
	static int nameId = 0;
	string name = "MiniGreyOneEngAnimator" + std::to_string(nameId);
	nameId++;

	MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
	assert(animator);
    updateGreyPlaneAnimation(animator);
	animator->start(Game::getGameTime());

}

void triggerRedPlaneTickAnimations(){
    static int id = 0;
    string redPlaneTickAnimationId ;
    if(id % 2 == 1){
        redPlaneTickAnimationId = "redJetRightTickAnimation" +  std::to_string(id/2);
        TimerTickAnimator::startTimeTickAnimator(redPlaneTickAnimationId, triggerRedJetRightAnimator );
    }else{
        redPlaneTickAnimationId = "redJetLeftTickAnimation" + std::to_string(id/2);
        TimerTickAnimator::startTimeTickAnimator(redPlaneTickAnimationId, triggerRedJetLeftAnimator );
    }
    id++;
    
}

void triggerMiniGreyJetTickAnimator(){
	static int nameId = 0;
	string name = "MiniGreyJetAnimator" + std::to_string(nameId);
	nameId++;

	MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
	assert(animator);
	animator->start(Game::getGameTime());
}

void triggerMedGreenDoubleEngAnimator(){
    static int nameId = 0;
    string name = "MedGreenDoubleEngAnimator" + std::to_string(nameId);
    nameId++;
    
    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());
    
}

void triggerMiniGreenOneEngAnimator(){
    static int nameId = 0;
    string name ;
    if(nameId % 2 == 0){
        name = "MiniGreenOneEngRightAnimator" + std::to_string(nameId/2);
    }else{
        name = "MiniGreenOneEngLeftAnimator" + std::to_string(nameId/2);
    }
    nameId++;
    
    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());
    
}

void triggerBigGreenIntroTickAnimators(){
    
    static int nameId = 0;
    string bigPlaneIntroAnimatorString = "BigGreenAnimator" + std::to_string(nameId); //Intro animator
    string bigPlaneMovingAnimId = "BigGreenMovingAnimator" +std::to_string(nameId);
    nameId++;
    
    if(! SpritesHolder::getSprite( ALIEN_SHIP , "BigGreen0" ) )
        return;
    
    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(bigPlaneIntroAnimatorString);
    assert(animator);
    
    MovingPathAnimator* animator2 = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(bigPlaneMovingAnimId);
    assert(animator2 );
    animator->start(Game::getGameTime());
    animator2->start(Game::getGameTime());
}

void triggerBigGreyIntroTickAnimators(){
    
    static int nameId = 0;
    string bigPlaneIntroAnimatorString = "BigGreyAnimator" + std::to_string(nameId); //Intro animator
    nameId++;
    
    if(! SpritesHolder::getSprite( ALIEN_SHIP , "BigGrey0" ) )
        return;
    
    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(bigPlaneIntroAnimatorString);
    assert(animator);
    animator->start(Game::getGameTime());
}


void triggerBigGreenStayStillTickAnimators(){
    
    static int nameId = 0;
    string bigPlaneIntroAnimatorString = "BigGreenAnimator" + std::to_string(nameId); //intro Animator
    string bigPlaneStayStillAnimatorString = "BigGreen1Animator" + std::to_string(nameId); //stay Still Animator
    nameId++;
    
    if(! SpritesHolder::getSprite( ALIEN_SHIP , "BigGreen0" ) )
        return;
    
    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(bigPlaneStayStillAnimatorString);
    assert(animator);
    MovingPathAnimator* prevAnimator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(bigPlaneIntroAnimatorString);
    assert(prevAnimator);
    prevAnimator->setState(ANIMATOR_FINISHED);
    prevAnimator->stop();
    animator->start(Game::getGameTime());
    
}
void triggerBigGreenOutroTickAnimators(){
    
    static int nameId = 0;
    string bigPlaneStayStillAnimatorString = "BigGreen1Animator" + std::to_string(nameId); //stay still animator
    string bigPlaneOutroAnimatorString = "BigGreen2Animator" + std::to_string(nameId); // outro animator
    nameId++;
    
    if(! SpritesHolder::getSprite( ALIEN_SHIP , "BigGreen0" ) )
        return;
    
    MovingPathAnimator* prevAnimator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(bigPlaneStayStillAnimatorString);
    assert(prevAnimator);
    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(bigPlaneOutroAnimatorString);
    assert(animator);
    
    prevAnimator->setState(ANIMATOR_FINISHED);
    prevAnimator->stop();
    animator->start(Game::getGameTime());

}

void triggerStartOfStageMaximizePlaneAnimator(){
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    
    SDL_Rect dRect = {
        (superAce->getDstRect().x - superAce->getMiniSuperAceDstRect().x)/5  ,
        (superAce->getDstRect().y - superAce->getMiniSuperAceDstRect().y)/5,
        (superAce->getDstRect().w - superAce->getMiniSuperAceDstRect().w)/5  ,
        (superAce->getDstRect().h - superAce->getMiniSuperAceDstRect().h)/5  ,
    };
    
    superAce->setDstRect({
        superAce->getSuperAceDstRect().x + dRect.x,
        superAce->getSuperAceDstRect().y + dRect.y,
        superAce->getSuperAceDstRect().w + dRect.w,
        superAce->getSuperAceDstRect().h + dRect.h,
    });
}


void triggerStartOfStageTakeOffTickAnimator(){
    AnimatorHolder::wakeUpAnimators(Game::getGameTime());

    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");
    superAce->doLoop();

    //maximize the plane
    TimerTickAnimator::startTimeTickAnimator("startOfStageMaximizePlaneTickAnimation", triggerStartOfStageMaximizePlaneAnimator );
    
}

void AnimatorHolder::triggerStartOfStageAnimators(){
    
    static unsigned times = 0;
    assert(times == 0);
    times++;
    
    //set items
    
    AnimatorHolder::superAceMovingAnimator();
    
    Sprite* initialAircraft = SpritesHolder::getSprite(TERRAIN, "spriteAircraftCarrier0");
    assert(initialAircraft);
    initialAircraft->setDstRectX(WIN_WIDTH/2-initialAircraft->getDstRect().w/2 +15 );
    initialAircraft->setDstRectY(WIN_HEIGHT-initialAircraft->getDstRect().h);
    
    Sprite* finishAircraft = SpritesHolder::getSprite(TERRAIN, "spriteAircraftCarrier1");
    assert(finishAircraft);
    finishAircraft->setDstRectX(WIN_WIDTH/2-initialAircraft->getDstRect().w/2 + 15 );
    finishAircraft->setDstRectY(-finishAircraft->getDstRect().h);

    //start the animators
    TimerTickAnimator::startTimeTickAnimator("startOfStageStartAnimatorsTickAnimation", Background::startBackgroundObjectAnimators );
    
    //take off the plane
    TimerTickAnimator::startTimeTickAnimator("startOfStageTakeOffTickAnimation", triggerStartOfStageTakeOffTickAnimator );
    
    //start enemy planes
    TimerTickAnimator::startTimeTickAnimator("startEnemyPlanesTickAnimation", AnimatorHolder::triggerstartEnemyPlanesTickAnimator );
	SoundHolder::playSound("propeller");

}

int setD(int big,int small){
    if(big-small >4){return 2;}
    else if(big-small >=2){return 1;}
    else if(big-small ==1){return 0;}
    else if(big-small ==0){return 0;}
    else{return 0;}
}

void updateEndOfStageAnimation(){

    static int times = 0;
    times++;
    cout<<times<<"\n";
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");
    
    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator("endOfStageMoveToCenterAnimator0");
    assert(animator);
    
    MovingPathAnimation* animation = animator->getMovingPathAnimation();
    assert(animation);

    if (!animator->isAlive()){
        return;
    }
    
    int dx =0;
    int dy =0;

    int dstX = superAce->getMiniSuperAceDstRect().x;
    int dstY = superAce->getMiniSuperAceDstRect().y;
    
    int superAceX = superAce->getDstRect().x;
    int superAceY = superAce->getDstRect().y;
    
    
    if (superAceX > dstX){
        dx = setD(superAceX,dstX);
        if (superAceY > dstY){
            dy = setD(superAceY,dstY);
            animation->changeDxDy(-dx, -dy);
        }
        else if (superAceY < dstY){
            dy = setD(dstY,superAceY);
            animation->changeDxDy(-dx, dy);
        }
        else{
            animation->changeDxDy(-dx, 0);
        }
    }
    else if (superAceX < dstX){
        dx = setD(dstX,superAceX);
        if (superAceY > dstY){
            dy = setD(superAceY,dstY);
            animation->changeDxDy(dx, -dy);
        }
        else if (superAceY < dstY){
            dy = setD(dstY,superAceY);
            animation->changeDxDy(dx,dy);
        }
        else{
            animation->changeDxDy(dx, 0);
        }
    }
    else{
        if (superAceY > dstY){
            dy = setD(superAceY,dstY);
            animation->changeDxDy(0, -dy);
        }
        else if (superAceY < dstY){
            dy = setD(dstY,superAceY);
            animation->changeDxDy(0, dy);
        }
        else{
        }
    }
    
    animator->start(Game::getGameTime());

}

void triggerEndOfStageCreateAircraftAnimator(){

    MovingPathAnimator* prevAnimator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator("endOfStageMoveToCenterAnimator0");

    assert(prevAnimator);

    prevAnimator->setState(ANIMATOR_FINISHED);
    prevAnimator->stop();

    Background::startBackgroundObjectAnimator("aircraftAnimator1");
}

void triggerEndOfStageMinimizePlaneAnimator(){
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    
    SDL_Rect dRect = {
        (superAce->getMiniSuperAceDstRect().x - superAce->getDstRect().x)/5  ,
        (superAce->getMiniSuperAceDstRect().y - superAce->getDstRect().y)/5,
        (superAce->getMiniSuperAceDstRect().w - superAce->getDstRect().w)/5  ,
        (superAce->getMiniSuperAceDstRect().h - superAce->getDstRect().h)/5  ,
    };
    
    superAce->setDstRect({
        superAce->getDstRect().x + dRect.x,
        superAce->getDstRect().y + dRect.y,
        superAce->getDstRect().w + dRect.w,
        superAce->getDstRect().h + dRect.h,
    });
}

void triggerEndOfStageLandPlaneAnimator(){
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    assert(superAce);
    superAce->doLoop();
    
    //minimize the plane
    TimerTickAnimator::startTimeTickAnimator("endOfStageMinimizePlaneTickAnimation", triggerEndOfStageMinimizePlaneAnimator );
    
}

void triggerEndOfStageStopBackgroundAnimator(){
    
    SpriteStringHolder::getSpriteString("shootingString")->setVisibility(true);
	

	SpriteStringHolder::getSpriteString("downString")->setVisibility(true);
	//cout << "shootingDownEnemies = " << std::to_string(Game::getDeadEnemies()) << endl;
	
	double shooting_down_percent_number = ((double)Game::getDeadEnemies() / (double)Game::getTotalEnemies()) * 100;
	string shooting_down_percent_str = (std::to_string((int)shooting_down_percent_number)) + "%";
	
	cout << "total enemies = " << Game::getTotalEnemies() << endl;
	cout << "total shooted enemies = " << Game::getDeadEnemies() << endl;
	cout << "shooting_down_percent_number = " << shooting_down_percent_number << endl;

	SpriteStringHolder::getSpriteString("shootingDownPercent")->changeString(shooting_down_percent_str, (WIN_WIDTH / 2) + 40, (WIN_HEIGHT / 2));
	SpriteStringHolder::getSpriteString("shootingDownPercent")->setVisibility(true);
    SpriteStringHolder::getSpriteString("shootingDownPercent")->setVisibility(true);
    SpriteStringHolder::getSpriteString("endingBonusString")->setVisibility(true);
    SpriteStringHolder::getSpriteString("pointsString")->setVisibility(true);

	//SpriteStringHolder::getSpriteString("points")->changeString();
	SpriteStringHolder::getSpriteString("points")->setVisibility(true);
    SpriteStringHolder::getSpriteString("letterR")->setVisibility(true);
    SpriteStringHolder::getSpriteString("1000Points")->setVisibility(true);
    SpriteStringHolder::getSpriteString("letterR")->setVisibility(true);
	SpriteStringHolder::getSpriteString("equals")->setVisibility(true);
	SpriteStringHolder::getSpriteString("pointsString2")->setVisibility(true);

	//last line with points
	SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
	assert(superAce);
	int last_points_number = superAce->getSuperAceLoops() * 1000;
	string last_points_str = std::to_string(last_points_number);
	SpriteStringHolder::getSpriteString("LastPoints")->changeString(last_points_str, (WIN_WIDTH / 2) + 50, (WIN_HEIGHT / 2) + 135);
	SpriteStringHolder::getSpriteString("LastPoints")->setVisibility(true);
	//
    Game::setState(END_OF_STAGE);
}

void AnimatorHolder::triggerEndOfStageAnimators(){
    static unsigned times = 0;
    assert(times == 0);
    times++;

    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    superAce->setMiniSuperAceDstRect({
        superAce->getMiniSuperAceDstRect().x,
        WIN_HEIGHT/4,
        superAce->getMiniSuperAceDstRect().w,
        superAce->getMiniSuperAceDstRect().h
    });
    
    AnimatorHolder::movingEnable = false;
    
    //move super ace to the center up of the screen
    TimerTickAnimator::startTimeTickAnimator("endOfStageMoveToCenterTickAnimation", updateEndOfStageAnimation );

    //create the finish aircraft
    TimerTickAnimator::startTimeTickAnimator("endOfStageCreateAircraftTickAnimation", triggerEndOfStageCreateAircraftAnimator );

    //land the plane
    TimerTickAnimator::startTimeTickAnimator("endOfStageLandPlaneTickAnimation", triggerEndOfStageLandPlaneAnimator );

    //stop the background and enable end text
    TimerTickAnimator::startTimeTickAnimator("endOfStageStopBackgroundTickAnimation", triggerEndOfStageStopBackgroundAnimator );

}

void triggerMedGreenSingleEngAnimator(){
	static int nameId = 0;
	string name = "MedGreenSingleEngAnimator" + std::to_string(nameId); //Intro animator
	nameId++;

	MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
	assert(animator);
	animator->start(Game::getGameTime());
}

void triggerDeathStarAnimator(){
    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator("deathStarAnimator0");
    assert(animator);
    animator->start(Game::getGameTime());
}

void triggerMedGreyDoubleAnimator(){
	static int nameId = 0;
	string name = "MedGreyDoubleEngAnimator" + std::to_string(nameId); 
	nameId++;

	MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
	assert(animator);
	animator->start(Game::getGameTime());
}
void triggerMedGreySingleAnimator(){
	static int nameId = 0;
	string name = "MedGreySingleEngAnimator" + std::to_string(nameId);
	nameId++;

	MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);

	assert(animator);
	animator->start(Game::getGameTime());
}
void triggerMedGreyTripleAnimator(){
	static int nameId = 0;
	string name = "MedGreyTripleEngAnimator" + std::to_string(nameId);
	nameId++;

	MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
	assert(animator);
	animator->start(Game::getGameTime());
}

void triggerMedGreyTripleEngAnimators(){
    
    static int nameId = 0;
    string name = "medGreyTripleEngTickAnimation" + std::to_string(nameId);
    
    assert(nameId<3);
    
    nameId++;
    
    //call a tick for 3 times
    TimerTickAnimator::startTimeTickAnimator(name, triggerMedGreyTripleAnimator);
    
}

void triggerMiniGreyDoubleEngAnimator(){
    static int nameId = 0;
    string name = "MiniGreyDoubleEngAnimator" + std::to_string(nameId);
    nameId++;
    
    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());
    
}

void triggerMedGreenTripleEngAnimator(){
    
     static int nameId = 0;
     string name = "MedGreenTripleEngAnimator" + std::to_string(nameId);
    
    assert(nameId<9);

    nameId++;
    MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
    assert(animator);
    animator->start(Game::getGameTime());
}

void triggerMedGreenTripleEngAnimators(){
    
    static int nameId = 0;
    string name = "medGreenTripleEngTickAnimation" + std::to_string(nameId);
    
    assert(nameId<3);
    
    nameId++;
    
    //call a tick for 3 times
    TimerTickAnimator::startTimeTickAnimator(name, triggerMedGreenTripleEngAnimator);
    
}

void AnimatorHolder::triggerstartEnemyPlanesTickAnimator(){
    static int times = 0;
    assert(times == 0);
    times++;
    
    AnimatorHolder::movingEnable = true;
    
    //remove starting logo
    SpriteStringHolder::getSpriteString("startingReadyLogo")->setVisibility(false);
    SpriteStringHolder::getSpriteString("startingPlayerLogo")->setVisibility(false);
    SpriteStringHolder::getSpriteString("numberOne")->setVisibility(false);
	//SoundHolder::playSound("gameplay");
	//play gameplay music
	if (SoundHolder::playMusic() == -1){
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
	}
    
    //Bullets
    TimerTickAnimator::startTimeTickAnimator("enemyBulletsTickAnimation", AnimatorHolder::triggerBullets);
    
    //Bonus Planes
    TimerTickAnimator::startTimeTickAnimator("redPlaneTickAnimations", triggerRedPlaneTickAnimations );
    
    //mini green Planes/jets
    TimerTickAnimator::startTimeTickAnimator("miniGreenOneEngTickAnimation", triggerMiniGreenOneEngAnimator );
    TimerTickAnimator::startTimeTickAnimator("miniGreenDoubleEngTickAnimation", triggerMiniGreenDoubleEngAnimator );
    TimerTickAnimator::startTimeTickAnimator("miniGreenJetTickAnimation", triggerMiniGreenJetAnimator );
    
    //mini  grey Planes/jets
    TimerTickAnimator::startTimeTickAnimator("miniGreyJetTickAnimation", triggerMiniGreyJetTickAnimator);
    TimerTickAnimator::startTimeTickAnimator("miniGreyOneEngTickAnimation", triggerMiniGreyOneEngAnimator);
    TimerTickAnimator::startTimeTickAnimator("miniGreyDoubleEngTickAnimation", triggerMiniGreyDoubleEngAnimator);
    
    
    //green medium plane
    TimerTickAnimator::startTimeTickAnimator("medGreenDoubleEngTickAnimation", triggerMedGreenDoubleEngAnimator);
    TimerTickAnimator::startTimeTickAnimator("medGreenSingleEngTickAnimation", triggerMedGreenSingleEngAnimator);
    TimerTickAnimator::startTimeTickAnimator("medGreenTripleEngTickAnimations", triggerMedGreenTripleEngAnimators);
    
    //grey medium plane
    TimerTickAnimator::startTimeTickAnimator("medGreyDoubleEngTickAnimation", triggerMedGreyDoubleAnimator);
    TimerTickAnimator::startTimeTickAnimator("medGreySingleEngTickAnimation", triggerMedGreySingleAnimator);
    TimerTickAnimator::startTimeTickAnimator("medGreyTripleEngTickAnimations", triggerMedGreyTripleEngAnimators);
    
	
    //big plane
    TimerTickAnimator::startTimeTickAnimator("bigGreenIntroTickAnimation", triggerBigGreenIntroTickAnimators );
    TimerTickAnimator::startTimeTickAnimator("bigGreyIntroTickAnimation", triggerBigGreyIntroTickAnimators );
    //WARNING DONT USE THE ABOVE 2 ANIMATORS
    //TimerTickAnimator::startTimeTickAnimator("bigGreenStayStillTickAnimation", triggerBigGreenStayStillTickAnimators );
    //TimerTickAnimator::startTimeTickAnimator("bigGreenOutroTickAnimation", triggerBigGreenOutroTickAnimators );
    
    //death star
    TimerTickAnimator::startTimeTickAnimator("deathStarTickAnimation", triggerDeathStarAnimator );
     
    //SuperAce* sp =(SuperAce*) SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    //sp->addSideFighters();
}

void AnimatorHolder::startTimeTickAnimators(){

    //start of stage
    TimerTickAnimator::startTimeTickAnimator("startOfStageTickAnimation", AnimatorHolder::triggerStartOfStageAnimators );

    //end of stage
    TimerTickAnimator::startTimeTickAnimator("endOfStageTickAnimation", AnimatorHolder::triggerEndOfStageAnimators );
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
        int repetition = mpa["repetition"].GetInt();
        std::string id = mpa["id"].GetString();
        std::string animationId = mpa["animationId"].GetString();
        std::string spriteId = mpa["spriteId"].GetString();
        int st = mpa["spriteType"].GetInt();
        SpriteType spriteType = SpriteType(st);
        assert( st < SPRITE_TYPE_SIZE );
        
        std::string id2,spriteId2,animationId2;
        for(int i = 0; i < repetition; ++i){
            id2 = id + std::to_string(i);
            spriteId2 = spriteId + std::to_string(i);
            animationId2 = animationId;
            //if (id.compare("MiniGreyOneEngAnimator") == 0)
              //  animationId2 +=  std::to_string(i);
            
            Sprite* sprite= SpritesHolder::getSprite(spriteType, spriteId2);
            assert(sprite);
            MovingPathAnimation* animation = (MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation(animationId2);
            assert(animation);
            MovingPathAnimator* animator  =	new MovingPathAnimator( id2, sprite, animation);
            assert(animator);
        }
    }
    
}
    
void AnimatorHolder::updateAllGreyPlaneAnimations(){
    
    MovingPathAnimator* grayPlaneAnimator;
    string grayPlaneAnimatorName, grayPlaneAnimationName;
    AnimatorHolder::AnimatorList::const_iterator it2 = getAnimatorHolder()->_running.end();
    AnimatorHolder::AnimatorList::const_iterator  it = getAnimatorHolder()->_running.begin();//_running.begin();
    
    while (it != getAnimatorHolder()->_running.end()){
        it2 = it;
        it2++;
        assert((*it));
		std::string str = string((*it)->getId());
		str.resize(str.size() - 1);

		if (str == "MiniGreyOneEngAnimator"){
			grayPlaneAnimator= (MovingPathAnimator*) (*it);
            updateGreyPlaneAnimation(grayPlaneAnimator);
		}


		if (str == "MiniGreyJetAnimator"){
			grayPlaneAnimator= (MovingPathAnimator*) (*it);
            updateGreyJetAnimation(grayPlaneAnimator);
        }

        if (str == "Chain2Chain1MiniGreenJetLeftAnimator" || str == "Chain2Chain1MiniGreenJetRightAnimator"){
            grayPlaneAnimator= (MovingPathAnimator*) (*it);
            updateGreenJetAnimation(grayPlaneAnimator);
        }



        it = it2;
    }
    
}

void updateGreyMedPlaneAnimation(MovingPathAnimator* grayMedPlaneAnimator){
	SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");

	MovingPathAnimation* grayMedPlaneAnimation = grayMedPlaneAnimator->getMovingPathAnimation();

	assert(grayMedPlaneAnimator);
	assert(grayMedPlaneAnimation);
	if (!grayMedPlaneAnimator->isAlive()){
		return;
	}

	int grayMedPlanePositionOnY = grayMedPlaneAnimator->getSprite()->getDstRect().y;
	int SuperAcePositionOnY = superAce->getDstRect().y;


	if (grayMedPlanePositionOnY > SuperAcePositionOnY - 400){

		//stop
		((EnemyFighter*)grayMedPlaneAnimator->getSprite())->setEnemyFireEnable(false);
		grayMedPlaneAnimator->setState(ANIMATOR_FINISHED);// _state = ANIMATOR_FINISHED;
		grayMedPlaneAnimator->stop();


	}
}


void updateGreyPlaneAnimation(MovingPathAnimator* grayJetAnimator){
    //assert(0);
    
    assert(grayJetAnimator);
    
    
    if (!grayJetAnimator->isAlive()){
        return;
    }
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");
    
    MovingPathAnimation* grayJetAnimation = grayJetAnimator->getMovingPathAnimation();
    assert(grayJetAnimation);
    
    if (grayJetAnimation->getPath().front()._dy < 0){
        return;
    }
    
    int grayJetPositionOnX = grayJetAnimator->getSprite()->getDstRect().x;
    int superAcePositionOnX = superAce->getDstRect().x;
    int superAcePositionOnY = superAce->getDstRect().y;
    
    int grayJetPositionOnY = grayJetAnimator->getSprite()->getDstRect().y;
    
    int apostashStonX = superAcePositionOnX - grayJetPositionOnX;
    
    if (apostashStonX < -10  ){
        //an o superace einai pio aristera apo to gray kai
        //to gray kinite deksia h den kinitai tote vale to na pigenei aristera
        if (grayJetAnimation->getPath().front()._dx >= 0){
            grayJetAnimator->setAnimation(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("MiniGreyOneEngLeftDownAnimation")));
        }
    }
    else if (apostashStonX > 10){
        if (grayJetAnimation->getPath().front()._dx <= 0){
            grayJetAnimator->setAnimation(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("MiniGreyOneEngRightDownAnimation")));
        }
        
    }
    else {
        if (grayJetAnimation->getPath().front()._dx != 0){
            grayJetAnimator->setAnimation(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("MiniGreyOneEngDownAnimation")));
        }
    }
    
    
    if (grayJetPositionOnY > superAcePositionOnY - 100){
        
        //stop
        ((EnemyFighter*)grayJetAnimator->getSprite())->setEnemyFireEnable(false);
        grayJetAnimator->setState(ANIMATOR_FINISHED);// _state = ANIMATOR_FINISHED;
        grayJetAnimator->stop();
        
        
    }
}


void  updateGreyJetAnimation(MovingPathAnimator* grayJetAnimator){
    
    assert(grayJetAnimator);
    
    if (!grayJetAnimator->isAlive()){
        return;
    }
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");
    
    MovingPathAnimation* grayJetAnimation = grayJetAnimator->getMovingPathAnimation();
    assert(grayJetAnimation);
    
    int grayJetPositionOnX = grayJetAnimator->getSprite()->getDstRect().x;
    int superAcePositionOnX = superAce->getDstRect().x;
    
    int grayJetPositionOnY = grayJetAnimator->getSprite()->getDstRect().y;
    
    int apostashStonX = superAcePositionOnX - grayJetPositionOnX;
    
    if (grayJetPositionOnY > WIN_HEIGHT -   50 || (apostashStonX < 10 && apostashStonX > -10)){
        grayJetAnimator->setAnimation(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("MiniGreyJetDownAnimation")));
        return;
    }
    
    if ( apostashStonX >=  10){
        if (grayJetAnimation->getPath().front()._dx <= 0){
            grayJetAnimator->setAnimation(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("GreyJetRightDownAnimation")));
        }
    }
    else if (apostashStonX <=  -10){
        if (grayJetAnimation->getPath().front()._dx >= 0){
            grayJetAnimator->setAnimation(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("GreyJetLeftDownAnimation")));
        }
    }
}

void  updateGreenJetAnimation(MovingPathAnimator* grayJetAnimator){
    
    assert(grayJetAnimator);
    
    if (!grayJetAnimator->isAlive()){
        return;
    }
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");
    
    MovingPathAnimation* grayJetAnimation = grayJetAnimator->getMovingPathAnimation();
    assert(grayJetAnimation);
    
    int grayJetPositionOnX = grayJetAnimator->getSprite()->getDstRect().x;
    int superAcePositionOnX = superAce->getDstRect().x;
    
    int grayJetPositionOnY = grayJetAnimator->getSprite()->getDstRect().y;
    
    int apostashStonX = superAcePositionOnX - grayJetPositionOnX;
    
    if (grayJetPositionOnY > WIN_HEIGHT -   50 || (apostashStonX < 10 && apostashStonX > -10)){
        grayJetAnimator->setAnimation(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("GreenJetDownAnimation")));
        return;
    }
    
    if ( apostashStonX >=  10){
        if (grayJetAnimation->getPath().front()._dx <= 0){
            grayJetAnimator->setAnimation(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("GreenJetRightDownAnimation")));
        }
    }
    else if (apostashStonX <=  -10){
        if (grayJetAnimation->getPath().front()._dx >= 0){
            grayJetAnimator->setAnimation(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("GreenJetLeftDownAnimation")));
        }
    }
}


void AnimatorHolder::superAceMovingAnimator(){
    
    static int nameId=0;
    string animatorMovingId = "animatorMovingId" + std::to_string(nameId);
    nameId++;
    
    //SuperAce
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");
    superAce->setVisibility(true);
    
    MovingPathAnimation* superAceManeuverAnimation = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("superAceMovingAnimation");
    assert(superAceManeuverAnimation);
    
    MovingPathAnimator* superAceManeuverAnimator = new MovingPathAnimator(animatorMovingId, superAce, (MovingPathAnimation*)superAceManeuverAnimation);
    assert(superAceManeuverAnimator);
    
    superAceManeuverAnimator->start(Game::getGameTime());

}

void AnimatorHolder::stopSuperAceMovingAnimator(){
    AnimatorHolder* ah = AnimatorHolder::getAnimatorHolder();
    MovingPathAnimator* superAceMovingAnimation = nullptr;
    
    string id = "animatorMovingId";
    string first;
    
    AnimatorMap::const_iterator it = ah->_map.begin();
    AnimatorMap::const_iterator it2;
    
    while (it != ah->_map.end()){
        it2=it;
        it2++;
        first = (string)(*it).first;
        if( first.find(id) != string::npos ){
            superAceMovingAnimation = (MovingPathAnimator*) (*it).second;
            assert(superAceMovingAnimation);
            superAceMovingAnimation->setState(ANIMATOR_FINISHED);
            superAceMovingAnimation->stop();
        }
        it=it2;
    }
}

int setDA(int big,int small){
    if(big-small >4){return 6;}
    if(big-small >3){return 4;}
    if(big-small ==3){return 2;}
    else if(big-small ==2){return 1;}
    else if(big-small ==1){return 0;}
    else if(big-small ==0){return 0;}
    else{return 0;}
}

bool  AnimatorHolder::updateSideFighterAnimation(string fighter){
    
    string animationName;
    int dstX;
    int dstY;
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");
    assert(superAce);
    
    SideFighter* sideFighter =(SideFighter*) superAce->getAttached(fighter);
    assert(sideFighter);

    if( fighter == LEFT_FIGHTER){
        animationName = "sideFighterAttachAnimationLeft";
        dstX = superAce->getDstRect().x - sideFighter->getDstRect().w;
        dstY = superAce->getDstRect().y;
    }
    else if( fighter == RIGHT_FIGHTER){
        animationName = "sideFighterAttachAnimationRight";
        dstX = superAce->getDstRect().x + superAce->getDstRect().w;
        dstY = superAce->getDstRect().y;
    }
    else{
        assert(0);
    }
    
    MovingPathAnimation* animation = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation(animationName);
    assert(animation);
    
    int dx = 0;
    int dy = 0;

    int currX = sideFighter->getDstRect().x;
    int currY = sideFighter->getDstRect().y;
    
    
    if (currX > dstX){
        dx = setDA(currX,dstX);
        if (currY > dstY){
            dy = setDA(currY,dstY);
            animation->changeDxDy(-dx, -dy);
        }
        else if (currY < dstY){
            dy = setDA(dstY,currY);
            animation->changeDxDy(-dx, dy);
        }
        else{
            animation->changeDxDy(-dx, 0);
        }
    }
    else if (currX < dstX){
        dx = setDA(dstX,currX);
        if (currY > dstY){
            dy = setDA(currY,dstY);
            animation->changeDxDy(dx, -dy);
        }
        else if (currY < dstY){
            dy = setDA(dstY,currY);
            animation->changeDxDy(dx,dy);
        }
        else{
            animation->changeDxDy(dx, 0);
        }
    }
    else{
        if (currY > dstY){
            dy = setDA(currY,dstY);
            animation->changeDxDy(0, -dy);
        }
        else if (currY < dstY){
            dy = setDA(dstY,currY);
            animation->changeDxDy(0, dy);
        }
        else{
        }
    }
    
    if( dx<2 && dx>-2 && dy<2 && dy>-2 ){
        //stop the animator
        
        MovingPathAnimator* animator;
        animator = (MovingPathAnimator*) AnimatorHolder::getAnimator("sideFighterAttachAnimatorRight");
        assert(animator);
        animator->setState(ANIMATOR_FINISHED);
        animator->stop();
        
        animator = (MovingPathAnimator*) AnimatorHolder::getAnimator("sideFighterAttachAnimatorLeft");
        assert(animator);
        animator->setState(ANIMATOR_FINISHED);
        animator->stop();
        
        //start the side fighter's moving animators
        
        if( fighter == LEFT_FIGHTER){
            animation = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationRight");
            assert(animation);
            animator = new MovingPathAnimator("LeftSideFighterAnimatorRight", sideFighter, animation);
            assert(animator);

            animation = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationLeft");
            assert(animation);
            animator	= new MovingPathAnimator("LeftSideFighterAnimatorLeft", sideFighter, animation);
            assert(animator);

        }
        else if( fighter == RIGHT_FIGHTER){
            animation = (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationRight");
            assert(animation);
            animator = new MovingPathAnimator( "RightSideFighterAnimatorRight", sideFighter, animation);
            assert(animator);
            
            animation=(MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("sideFighterAnimationLeft");
            assert(animation);
            animator= new MovingPathAnimator("RightSideFighterAnimatorLeft", sideFighter, animation);
            assert(animator);
        }
        else{
            assert(0);
        }

        return false;
    }
    
    return true;
}

void AnimatorHolder::createUpdateScoreAnimator(SDL_Rect rect,int points){

    static int nameId=0;
    string scoreSpriteId = "scoreSprite" + std::to_string(nameId);
    string scoreAnimatorId = "scoreAnimator" + std::to_string(nameId);
    unsigned frameNo = 0;
    nameId++;
    rect.x = rect.x + rect.w/2; 
    rect.y = rect.y + rect.h/2;
    rect.w = 30;
    rect.h = 20;

    AnimationFilm* scoreFilm = AnimationFilmHolder::Get()->GetFilm("scores");
    assert(scoreFilm);
    
    switch (points) {
        case 1000:{
            frameNo = 0;
            break;
        }
        case 1500:{
            frameNo = 2;
            break;
        }
        case 2000:{
            frameNo = 1;
            break;
        }
        default:{
            assert(0);
            break;
        }
    }
    
    Sprite* scoreSprite = new Sprite(scoreSpriteId, frameNo, rect , {0,0}, true, GAME_INFO, scoreFilm);
    assert(scoreSprite);
    
    Animation* scoreAnimation = AnimationHolder::getAnimationHolder()->getAnimation("powerUp");
    assert(scoreAnimation);
    
    MovingAnimator* scoreAnimator = new MovingAnimator(scoreAnimatorId, scoreSprite, (MovingAnimation*)scoreAnimation);
    assert(scoreAnimator);
    
    scoreAnimator->start(Game::getGameTime());

}


