#include "Game.hpp"
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"


#include "TickAnimation.h"
#include "TimerTickAnimator.h"
#include "MovingAnimation.h"

bool Game::OnInit(){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}
    
	InitGamePad();
	
	//std::cout << SDL_GameControllerAddMapping("0,X360 Controller, a:b6,b:b10");
    InitWindow();
	
    InitRenderer();
    
    InitGame();
    
    return true;
}

void f(){
	/*MovingPathAnimator* superAceEndingAnimator =
		(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceEndingAnimator");
	
	superAceEndingAnimator->start(Game::getGameTime());*/

	MovingPathAnimator* superAceEndingAnimator =
		(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceEndingAnimator");

	superAceEndingAnimator->start(Game::getGameTime());

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

void createTimeTickAnimator(){
    
    animid_t id = "tickAnimation";
    delay_t _delay = 10000; //10 sec
    unsigned _repetitions = 1;
	cout << "AAAAA";
    TickAnimation* tickAnimation = new TickAnimation(id ,_delay ,_repetitions ,f);
    
    tickAnimation = (TickAnimation*)AnimationHolder::getAnimationHolder()->getAnimation(id);
    assert(tickAnimation);
    tickAnimation->setOnTick(f);
    
    TimerTickAnimator* timerTickAnimator = new TimerTickAnimator(tickAnimation);

    AnimatorHolder::getAnimatorHolder()->Register( timerTickAnimator );

    //timerTickAnimator->start( Game::getGameTime() );
}

void Game::InitGame(){
    InitData();
    SoundHolder::initSounds();
    InitSuperAceAnimator();
    LoadGameInfo("config.json");
    
    InitBackground();
    
    InitGameInfo();
    
	InitSuperAceAnimator();
    
	
    createTimeTickAnimator();
}


void Game::InitGamePad(){
	for (int i = 0; i < SDL_NumJoysticks(); ++i){
		if (SDL_IsGameController(i)){

			_controller = SDL_GameControllerOpen(i);
			std::cout << SDL_GameControllerMapping(_controller) << endl;
			break;
		}
	}
}
void Game::InitSuperAceAnimator(){
    

    animid_t id = "SuperAceAnimation";
    
    Sprite* superAce = SpritesHolder::getSpritesHolder()->getSprites(SUPER_ACE)->front();
	
	MovingPathAnimation* superAceStartingAnimation =
		(MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("superAceStartingAnimation");
	MovingPathAnimator* superAceStartingAnimator  =	new MovingPathAnimator(
		"SuperAceStartingAnimator", superAce, superAceStartingAnimation
		);

	MovingPathAnimation* superAceEndingAnimation =
		(MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("superAceEndingAnimation");
	MovingPathAnimator* superAceEndingAnimator = new MovingPathAnimator(
		"SuperAceEndingAnimator", superAce, superAceEndingAnimation
	);
    
    MovingPathAnimation* superAceMovingAnimation =
		(MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("superAceMovingAnimation");
	MovingPathAnimator* superAceMovingAnimator  =	new MovingPathAnimator(
		"SuperAceMovingAnimator", superAce, superAceMovingAnimation
		);
	
	MovingPathAnimation* superAceAnimationManeuver	=
			(MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("superAceAnimationManeuver");	
	MovingPathAnimator* superAceAnimatorManeuever	= new MovingPathAnimator(
		"SuperAceAnimatorManeuver", superAce, superAceAnimationManeuver
		);



    MovingPathAnimation* superAceAnimationUp = 
		(MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("superAceAnimationUp");
	MovingPathAnimator* superAceAnimatorUp	 = new MovingPathAnimator(
		"SuperAceAnimatorUp", superAce, superAceAnimationUp
		);




	MovingPathAnimation* superAceAnimationDown = 
		(MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("superAceAnimationDown");
	MovingPathAnimator* superAceAnimatorDown = new MovingPathAnimator(
		"SuperAceAnimatorDown", superAce, superAceAnimationDown
		);


	MovingPathAnimation* superAceAnimationRight =
		(MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("superAceAnimationRight");
	MovingPathAnimator* superAceAnimatorRight = new MovingPathAnimator(
		"SuperAceAnimatorRight", superAce, superAceAnimationRight
		);

    MovingPathAnimation* superAceAnimationRightRight =
    (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("superAceAnimationRightRight");
    MovingPathAnimator* superAceAnimatorRightRight = new MovingPathAnimator(
                                                                       "SuperAceAnimatorRightRight", superAce, superAceAnimationRightRight
                                                                       );

	MovingPathAnimation* superAceAnimationLeft	= 
		(MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("superAceAnimationLeft");
	MovingPathAnimator* superAceAnimatorLeft	= new MovingPathAnimator(
		"SuperAceAnimatorLeft", superAce, superAceAnimationLeft
		);
    
    MovingPathAnimation* superAceAnimationLeftLeft	=
    (MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("superAceAnimationLeftLeft");
    MovingPathAnimator* superAceAnimatorLeftLeft	= new MovingPathAnimator(
                                                                         "SuperAceAnimatorLeftLeft", superAce, superAceAnimationLeftLeft
                                                                         );

	AnimatorHolder::Register(superAceMovingAnimator);
	AnimatorHolder::Register(superAceAnimatorUp);
	AnimatorHolder::Register(superAceAnimatorRight);
	AnimatorHolder::Register(superAceAnimatorRightRight);
	AnimatorHolder::Register(superAceAnimatorDown);
	AnimatorHolder::Register(superAceAnimatorLeft);
	AnimatorHolder::Register(superAceAnimatorLeftLeft);
	AnimatorHolder::Register(superAceAnimatorManeuever);
	AnimatorHolder::Register(superAceStartingAnimator);
	AnimatorHolder::Register(superAceEndingAnimator);

}


bool Game::InitWindow(){
    static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;
    
    _window = SDL_CreateWindow("Main Menu", WIN_X, WIN_Y, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
    if (_window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    return true;
}

bool Game::InitRenderer(){
    static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;
    
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr){
        SDL_DestroyWindow(_window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    return true;
}

bool Game::InitData(){
    static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;
    
    
    AnimationFilmHolder* anFh = AnimationFilmHolder::Get();
	anFh->Load("films.json", _renderer);
    
    SpritesHolder* sh = SpritesHolder::getSpritesHolder();
    sh->Load("sprites.json");
    
    AnimationHolder* anh = AnimationHolder::getAnimationHolder();
    anh->Load("animations.json");
    return true;
}

bool Game::InitBackground(){
    static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;
    
    SpritesHolder::getSpritesHolder()->add((Sprite*)Background::Get());

    return true;
}

using namespace rapidjson;
void    Game::LoadGameInfo (const std::string& cataloge){
    std::string line, text;
    
    static  std::string  dataFilePath = SRC_PATH + string(cataloge);
    
    std::ifstream file(dataFilePath);
    
    while(std::getline(file, line))
    {
        text += line + "\n";
    }
    const char* data = text.c_str();
    
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
    Document document;
    document.Parse(data);
    assert(document.IsObject());
    superAce->setSuperAceLives(document["superAceLives"].GetInt());
    superAce->setSuperAceLoops(document["superAceLoops"].GetInt());
    //_remaining_loops_num =document["superAceLoops"].GetInt();
    _highScore = document["highScore"].GetInt();
    _spriteSize = document["spriteSize"].GetDouble();
    assert(document["powerUpsOfStage"].IsArray());
    const Value& powerUps= document["powerUpsOfStage"];
    for (rapidjson::SizeType i = 0; i < powerUps.Size(); i++)
    {
        unsigned u = powerUps[i].GetUint();
        assert(u < 7 );
        setNextPowerUpType(powerUps[i].GetUint());
    }
}

void Game::updateHighScoreJson(const std::string& cataloge){
    std::string line, text;
    
    static  std::string  dataFilePath = SRC_PATH + string(cataloge);
    
    std::ifstream file(dataFilePath);
    
    while(std::getline(file, line))
    {
        text += line + "\n";
    }
    const char* data = text.c_str();
    Document document;
    document.Parse(data);
    assert(document.IsObject());
    //_highScore = document["highScore"].GetInt();
    if(_highScore > document["highScore"].GetInt()){
        document["highScore"].SetInt(_highScore);
        //document.AddMember("position", document["highscore"], document);
        //document["highScore"].SetObject();
        cout<<"NEW HIGHSCORE: "<<_highScore<<endl;
    }
}

bool Game::InitGameInfo(){
    static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;
    
    SpriteStringHolder::addSpriteString("scoreString", new SpriteString("SCORE",20,10));
    SpriteStringHolder::addSpriteString("highString", new SpriteString("HIGH",200,10));
    SpriteStringHolder::addSpriteString("highScoreString", new SpriteString("SCORE",250,10));
    
    SpriteStringHolder::addSpriteString("fpsString", new SpriteString("FPS",450,10));
    SpriteStringHolder::addSpriteString("fps", new SpriteString("0000",450,30));

    SuperAce* superAce = (SuperAce*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
    std::string remainingLoopsString = "";
    for(int i = 0; i < superAce->getSuperAceLoops(); i++){
       remainingLoopsString += "R";
	}
    
    std::string remainingLivesString = "";
    for(int i = 0; i < superAce->getSuperAceLives(); i++){
        remainingLivesString += "L";
    }
	
    string score = std::to_string(_score);
    string highScore = std::to_string(_highScore);

    SpriteStringHolder::addSpriteString("press", new SpriteString( "PRESS", 150 ,410) );
    SpriteStringHolder::addSpriteString("space", new SpriteString( "SPACE", 220 ,410) );
    SpriteStringHolder::addSpriteString("for", new SpriteString( "FOR", 285 ,410) );
    SpriteStringHolder::addSpriteString("exit2", new SpriteString( "EXIT", 325 ,410) );
    SpriteStringHolder::getSpriteString("press")->setVisibility(false);
    SpriteStringHolder::getSpriteString("space")->setVisibility(false);
    SpriteStringHolder::getSpriteString("for")->setVisibility(false);
    SpriteStringHolder::getSpriteString("exit2")->setVisibility(false);
    
    SpriteStringHolder::addSpriteString("game", new SpriteString( "GAME", 196 ,110) );
    SpriteStringHolder::getSpriteString("game")->setVisibility(false);
    SpriteStringHolder::addSpriteString("over", new SpriteString( "OVER", 256 ,110) );
    SpriteStringHolder::getSpriteString("over")->setVisibility(false);
    SpriteStringHolder::addSpriteString("score", new SpriteString( score , 20 ,30) );
    SpriteStringHolder::addSpriteString("highScore", new SpriteString( highScore , WIN_WIDTH/2 - (int) (highScore.size()*6), 30) );
    SpriteStringHolder::addSpriteString("remainingLoops", new SpriteString(remainingLoopsString, WIN_WIDTH - superAce->getSuperAceLoops()*12 -5, WIN_HEIGHT - 15) );
    SpriteStringHolder::addSpriteString("remainingLives", new SpriteString(remainingLivesString, /*WIN_WIDTH - superAce->getSuperAceLives()*12*/ 5, WIN_HEIGHT - 15) );
    SpriteStringHolder::getSpriteString("remainingLoops")->setVisibility(true);
    SpriteStringHolder::addSpriteString("startingReadyLogo", new SpriteString("READY", (WIN_WIDTH / 2)-40, WIN_HEIGHT / 2) );
    SpriteStringHolder::addSpriteString("startingPlayerLogo", new SpriteString("PLAYER", (WIN_WIDTH / 2)-40, (WIN_HEIGHT / 2)+20) );
    SpriteStringHolder::addSpriteString("numberOne", new SpriteString("1", (WIN_WIDTH / 2)+32, (WIN_HEIGHT / 2)+20) );

    SpriteStringHolder::addSpriteString("pause", new SpriteString("PAUSE", (WIN_WIDTH / 2 -(5*6)), (WIN_HEIGHT / 2) ) );
    SpriteStringHolder::getSpriteString("pause")->setVisibility(false);
    SpriteStringHolder::addSpriteString("exit", new SpriteString("EXIT", (WIN_WIDTH / 2 -(5*6)), (WIN_HEIGHT / 2 - 20) ) );
    SpriteStringHolder::getSpriteString("exit")->setVisibility(false);
    
    /*change letter M with a pointer*/
    SpriteStringHolder::addSpriteString("currsorUp", new SpriteString("M", (WIN_WIDTH / 2 -(5*6) - 20), (WIN_HEIGHT / 2 - 20) ) );
    SpriteStringHolder::getSpriteString("currsorUp")->setVisibility(false);
    SpriteStringHolder::addSpriteString("currsorDown", new SpriteString("M", (WIN_WIDTH / 2 -(5*6) - 20), (WIN_HEIGHT / 2) ) );
    SpriteStringHolder::getSpriteString("currsorDown")->setVisibility(false);
    
    SpriteStringHolder::addSpriteString("shootingString", new SpriteString("SHOOTING", (WIN_WIDTH / 2) - 150, (WIN_HEIGHT / 2)) );
    SpriteStringHolder::getSpriteString("shootingString")->setVisibility(false);
    SpriteStringHolder::addSpriteString("downString", new SpriteString("DOWN", (WIN_WIDTH / 2)-40, (WIN_HEIGHT / 2)) );
    SpriteStringHolder::getSpriteString("downString")->setVisibility(false);
    SpriteStringHolder::addSpriteString("shootingDownPercent", new SpriteString("100%", (WIN_WIDTH / 2) + 40, (WIN_HEIGHT / 2)) );
    SpriteStringHolder::getSpriteString("shootingDownPercent")->setVisibility(false);
    SpriteStringHolder::addSpriteString("endingBonusString", new SpriteString("BONUS", (WIN_WIDTH / 2) -70, (WIN_HEIGHT / 2)+70) );
    SpriteStringHolder::getSpriteString("endingBonusString")->setVisibility(false);
    SpriteStringHolder::addSpriteString("pointsString", new SpriteString("PTS", (WIN_WIDTH / 2) +5, (WIN_HEIGHT / 2)+95) );
    SpriteStringHolder::getSpriteString("pointsString")->setVisibility(false);
    SpriteStringHolder::addSpriteString("points", new SpriteString("100000", (WIN_WIDTH / 2)-90, (WIN_HEIGHT / 2) + 95) );
    SpriteStringHolder::getSpriteString("points")->setVisibility(false);
    SpriteStringHolder::addSpriteString("letterR", new SpriteString("R*", (WIN_WIDTH / 2) - 90, (WIN_HEIGHT / 2)+135) );
    SpriteStringHolder::getSpriteString("letterR")->setVisibility(false);
    SpriteStringHolder::addSpriteString("1000Points", new SpriteString("1000", (WIN_WIDTH / 2) - 60, (WIN_HEIGHT / 2) + 135) );
    SpriteStringHolder::getSpriteString("1000Points")->setVisibility(false);
    SpriteStringHolder::addSpriteString("equals", new	SpriteString("=", (WIN_WIDTH / 2) + 30, (WIN_HEIGHT / 2) + 135) );
    SpriteStringHolder::getSpriteString("equals")->setVisibility(false);
    return true;
}

