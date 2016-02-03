#include "AnimatorHolder.h"

void updateGreyPlaneAnimation(MovingPathAnimator* grayJetAnimator);
void updateGreyJetAnimation(MovingPathAnimator* grayJetAnimator);
void triggerMediumGreenPlaneAnimator();
//void  updateGreenJetAnimation(MovingPathAnimator* grayJetAnimator);

AnimatorHolder* AnimatorHolder::_holder = 0;

void AnimatorHolder::Register(Animator* a) {
    assert(AnimatorHolder::getAnimatorHolder()->_map[a->getId()] == nullptr);
    
    AnimatorHolder::getAnimatorHolder()->_map[a->getId()] = a;
    AnimatorHolder::getAnimatorHolder()->_suspended.push_back(a);
}
void AnimatorHolder::cancel(Animator* a) {
    AnimatorHolder::getAnimatorHolder()->_suspended.remove(a);
    
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
	//SuperAce* superAce =
	//	(SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");

	//MovingPathAnimator* startingAnimator = (MovingPathAnimator*) AnimatorHolder::getAnimator("SuperAceStartingAnimator0");

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

void triggerSuperAceMovingPathAnimator(){
    MovingPathAnimator* movingSuperAce = (MovingPathAnimator*) AnimatorHolder::getAnimator("SuperAceMovingAnimator0");
    assert(movingSuperAce);
    movingSuperAce->start(Game::getGameTime());
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
    string name = "MiniGreenJetAnimator" + std::to_string(nameId);
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
    nameId++;
    
    if(! SpritesHolder::getSprite( ALIEN_SHIP , "BigGreen0" ) )
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

int setD(int big,int small){
    if(big-small >4){ cout<<4<<endl;return 4;}
    else if(big-small >=2){ cout<<2<<endl;return 2;}
    else if(big-small ==1){ cout<<1<<endl;return 0;}
    else if(big-small ==0){ cout<<0<<endl;return 0;}
    else{cout<<0<<endl;return 0;}
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
    int dstX = WIN_WIDTH/2-superAce->getDstRect().w/2;
    int dstY = 100;
    
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

void triggerEndOfStageLandPlaneAnimator(){
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    assert(superAce);
    superAce->doManeuever();
}

void triggerEndOfStageStopBackgroundAnimator(){
    
    SpriteStringHolder::getSpriteString("shootingString")->setVisibility(true);
    SpriteStringHolder::getSpriteString("downString")->setVisibility(true);
    SpriteStringHolder::getSpriteString("shootingDownPercent")->setVisibility(true);
    SpriteStringHolder::getSpriteString("endingBonusString")->setVisibility(true);
    SpriteStringHolder::getSpriteString("pointsString")->setVisibility(true);
    SpriteStringHolder::getSpriteString("points")->setVisibility(true);
    SpriteStringHolder::getSpriteString("letterR")->setVisibility(true);
    SpriteStringHolder::getSpriteString("1000Points")->setVisibility(true);
    SpriteStringHolder::getSpriteString("letterR")->setVisibility(true);
    
    Game::setState(END_OF_STAGE);
}

void AnimatorHolder::triggerEndOfStageAnimators(){
    static unsigned times = 0;
    assert(times == 0);
    times++;

    //move super ace to the center up of the screen
    TimerTickAnimator::startTimeTickAnimator("endOfStageMoveToCenterTickAnimation", updateEndOfStageAnimation );    //repeatition 100

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
void triggerMedGreenTripleEngAnimator(){
	static int nameId = 0;
	string name = "MedGreenTripleEngAnimator" + std::to_string(nameId);
	nameId++;

	MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
	assert(animator);
	animator->start(Game::getGameTime());
}
void triggerMiniGreyDoubleEngAnimator(){
	static int nameId = 0;
	string name = "MiniGreyDoubleEngAnimator" + std::to_string(nameId);
	nameId++;

	MovingPathAnimator* animator = (MovingPathAnimator*)AnimatorHolder::getAnimatorHolder()->getAnimator(name);
	assert(animator);
	animator->start(Game::getGameTime());

}
void AnimatorHolder::startTimeTickAnimators(){
    
    //SuperAce
    //TimerTickAnimator::startTimeTickAnimator("superAceMovingPathTickAnimation", triggerSuperAceMovingPathAnimator );
    
    //Bullets
    //TimerTickAnimator::startTimeTickAnimator("enemyBulletsTickAnimation", AnimatorHolder::triggerBullets);
    
    //Bonus Planes
    //TimerTickAnimator::startTimeTickAnimator("redPlaneTickAnimations", triggerRedPlaneTickAnimations );
     
    //mini green Planes/jets
    //TimerTickAnimator::startTimeTickAnimator("miniGreenOneEngTickAnimation", triggerMiniGreenOneEngAnimator );
    //TimerTickAnimator::startTimeTickAnimator("miniGreenDoubleEngTickAnimation", triggerMiniGreenDoubleEngAnimator );
    //TimerTickAnimator::startTimeTickAnimator("miniGreenJetTickAnimation", triggerMiniGreenJetAnimator );

	//mini  grey Planes/jets
    TimerTickAnimator::startTimeTickAnimator("miniGreyJetTickAnimation", triggerMiniGreyJetTickAnimator);
	//TimerTickAnimator::startTimeTickAnimator("miniGreyOneEngTickAnimation", triggerMiniGreyOneEngAnimator);
	//TimerTickAnimator::startTimeTickAnimator("miniGreyDoubleEngTickAnimation", triggerMiniGreyDoubleEngAnimator);


	//green medium plane
	//TimerTickAnimator::startTimeTickAnimator("medGreenDoubleEngTickAnimation", triggerMedGreenDoubleEngAnimator);
	//TimerTickAnimator::startTimeTickAnimator("medGreenSingleEngTickAnimation", triggerMedGreenSingleEngAnimator);
	//TimerTickAnimator::startTimeTickAnimator("medGreenTripleEngTickAnimation", triggerMedGreenTripleEngAnimator);

	//grey medium plane
	//TimerTickAnimator::startTimeTickAnimator("medGreyDoubleEngTickAnimation", triggerMedGreyDoubleAnimator);
	//TimerTickAnimator::startTimeTickAnimator("medGreySingleEngTickAnimation", triggerMedGreySingleAnimator);
	//TimerTickAnimator::startTimeTickAnimator("medGreyTripleEngTickAnimation", triggerMedGreyTripleAnimator);


    //big plane
    //TimerTickAnimator::startTimeTickAnimator("bigGreenIntroTickAnimation", triggerBigGreenIntroTickAnimators );
    //TimerTickAnimator::startTimeTickAnimator("bigGreenStayStillTickAnimation", triggerBigGreenStayStillTickAnimators );
    //TimerTickAnimator::startTimeTickAnimator("bigGreenOutroTickAnimation", triggerBigGreenOutroTickAnimators );
    
    //death star
    //TimerTickAnimator::startTimeTickAnimator("deathStarTickAnimation", triggerDeathStarAnimator );
    
    //end of stage
    //TimerTickAnimator::startTimeTickAnimator("endOfStageTickAnimation", AnimatorHolder::triggerEndOfStageAnimators );
    
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
            if (id.compare("MiniGreyOneEngAnimator") == 0)
                animationId2 +=  std::to_string(i);
            
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

       /* if (str == "Chain2Chain1MiniGreenJetAnimator"){
            grayPlaneAnimator= (MovingPathAnimator*) (*it);
            updateGreenJetAnimation(grayPlaneAnimator);
        }*/



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
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");
    
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
    path._delay = 40;
    path._visibility = true;
    
    
    
    int superAcePositionOnX = superAce->getDstRect().x;
    int grayJetPositionOnX = grayJetAnimator->getSprite()->getDstRect().x;
    
    
    int grayJetPositionOnY = grayJetAnimator->getSprite()->getDstRect().y;
    int SuperAcePositionOnY = superAce->getDstRect().y;
    
    
    
    
    if (grayJetPositionOnX > superAcePositionOnX + 10){
        //an o superace einai pio aristera apo to gray kai
        //to gray kinite deksia h den kinitai tote vale to na pigenei aristera
        if (grayJetAnimation->getPath().front()._dx >= 0){
            path._dx = -4;
            path._dy = 4;
            std::list<PathEntry> p;
            p.push_front(path);
            grayJetAnimation->setPath(p);
        }
    }
    else if (grayJetPositionOnX < superAcePositionOnX - 10){
        if (grayJetAnimation->getPath().front()._dx <= 0){
            path._dx = 4;
            path._dy = 4;
            std::list<PathEntry> p;
            p.push_front(path);
            grayJetAnimation->setPath(p);
        }
        
    }
    else {
        //do not move on x axis
        if (grayJetAnimation->getPath().front()._dx != 0){
            
            path._dx = 0;
            path._dy = 4;
            std::list<PathEntry> p;
            p.push_front(path);
            grayJetAnimation->setPath(p);
        }
    }
    
    
    if (grayJetPositionOnY > SuperAcePositionOnY - 100){
        
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
	//int superAcePositionOnY = superAce->getDstRect().y;

	int apostashStonX = superAcePositionOnX - grayJetPositionOnY;
	if (apostashStonX < 0){
		apostashStonX = apostashStonX*(-1);
	}
	if (grayJetPositionOnY > WIN_HEIGHT - 250 || apostashStonX < 50){
		//cout << "DOWN" << endl;
		grayJetAnimation->changeDxDy(0, 4);
		
		grayJetAnimator->getSprite()->setFrame(0);
		return;
	}

	if (superAcePositionOnX > grayJetPositionOnX +10){
    
		if (grayJetAnimation->getPath().front()._dx <= 0){
    
			grayJetAnimation->setPath(((MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("GreyJetRightDownAnimation"))->getPath());
		}
	}
	else if (superAcePositionOnX < grayJetPositionOnX -10){
		if (grayJetAnimation->getPath().front()._dx >= 0){
			grayJetAnimation->setPath(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("GreyJetLeftDownAnimation"))->getPath());
    
		}
	}
}

/*void  updateGreenJetAnimation(MovingPathAnimator* grayJetAnimator){
    
    assert(grayJetAnimator);
    
    if (!grayJetAnimator->isAlive()){
        return;
    }
    std::size_t found;
    
    
    
    found = grayJetAnimator->getId().find("Chain2Chain1MiniGreenJetAnimator");
    if (found == 0){
        SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce0");
        
        MovingPathAnimation* grayJetAnimation = grayJetAnimator->getMovingPathAnimation();
        assert(grayJetAnimation);
        
        int grayJetPositionOnX = grayJetAnimator->getSprite()->getDstRect().x;
        int superAcePositionOnX = superAce->getDstRect().x;
        
        int grayJetPositionOnY = grayJetAnimator->getSprite()->getDstRect().y;
        
        int apostashStonX = superAcePositionOnX - grayJetPositionOnY;
        if (apostashStonX < 0){
            apostashStonX = apostashStonX*(-1);
        }
        if (grayJetPositionOnY > WIN_HEIGHT - 80 ||   apostashStonX < 50){
            //cout << "DOWN" << endl;
            grayJetAnimation->changeDxDy(0, 4);
            
            grayJetAnimator->getSprite()->setFrame(0);
            return;
        }
        
        if (superAcePositionOnX +10 > grayJetPositionOnX ){
            
            if (grayJetAnimation->getPath().front()._dx <= 0){
                
                grayJetAnimation->setPath(((MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("GreenJetRightDownAnimation"))->getPath());
            }
        }
        else if (superAcePositionOnX -10< grayJetPositionOnX ){
            if (grayJetAnimation->getPath().front()._dx >= 0){
                grayJetAnimation->setPath(((MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("GreenJetLeftDownAnimation"))->getPath());
                
            }
        }
    }
}*/


