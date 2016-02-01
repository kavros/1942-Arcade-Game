#include "Game.hpp"
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"

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

void Game::InitGame(){
    InitData();
    SoundHolder::initSounds();

    LoadGameInfo("config.json");
    
    InitBackground();
    
    InitGameInfo();
        
    AnimatorHolder::startTimeTickAnimators();
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


bool Game::InitWindow(){
    static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;
    
    SDL_DisplayMode current;
    if(SDL_GetCurrentDisplayMode(0, &current))
        SDL_Log("Could not get display mode for video display #%d: %s", 0, SDL_GetError());
    
    _window = SDL_CreateWindow("1942", current.w, current.h , WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
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
    
    SpritesHolder::Load("sprites.json");
    
    AnimationHolder* anh = AnimationHolder::getAnimationHolder();
    anh->Load("animations.json");
    AnimatorHolder::getAnimatorHolder()->Load("animators.json");
    return true;
}

bool Game::InitBackground(){
    static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;
    
    Background::Get();

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
    
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");
    Document document;
    document.Parse(data);
    assert(document.IsObject());
    superAce->setSuperAceLives(document["superAceLives"].GetInt());
    superAce->setSuperAceLoops(document["superAceLoops"].GetInt());
    //_remaining_loops_num =document["superAceLoops"].GetInt();
    _highScore = document["highScore"].GetInt();
    _spriteSize = document["spriteSize"].GetDouble();
    assert(document["powerUpsOfStage"].IsArray());
    SoundHolder::setMute(document["mute"].GetBool());
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
    SpriteStringHolder::addSpriteString("highString", new SpriteString("HIGH",(WIN_WIDTH/2)-56,10));
    SpriteStringHolder::addSpriteString("highScoreString", new SpriteString("SCORE",(WIN_WIDTH/2)-6,10));
    
    SpriteStringHolder::addSpriteString("fpsString", new SpriteString("FPS",WIN_WIDTH-62,10));
    SpriteStringHolder::addSpriteString("fps", new SpriteString("0000",WIN_WIDTH-62,30));

    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");
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

    SpriteStringHolder::addSpriteString("press", new SpriteString( "PRESS", (WIN_WIDTH/2)- 106 ,410) );
    SpriteStringHolder::addSpriteString("space", new SpriteString( "ENTER", (WIN_WIDTH/2) - 36 ,410) );
    SpriteStringHolder::addSpriteString("for", new SpriteString( "FOR", (WIN_WIDTH/2)+ 29 ,410) );
    SpriteStringHolder::addSpriteString("exit2", new SpriteString( "EXIT", (WIN_WIDTH/2)+ 69 ,410) );
    SpriteStringHolder::getSpriteString("press")->setVisibility(false);
    SpriteStringHolder::getSpriteString("space")->setVisibility(false);
    SpriteStringHolder::getSpriteString("for")->setVisibility(false);
    SpriteStringHolder::getSpriteString("exit2")->setVisibility(false);
    
    SpriteStringHolder::addSpriteString("game", new SpriteString( "GAME", (WIN_WIDTH/2)- 60 ,110) );
    SpriteStringHolder::getSpriteString("game")->setVisibility(false);
    SpriteStringHolder::addSpriteString("over", new SpriteString( "OVER", (WIN_WIDTH/2) ,110) );
    SpriteStringHolder::getSpriteString("over")->setVisibility(false);
    SpriteStringHolder::addSpriteString("score", new SpriteString( score , 20 ,30) );
    SpriteStringHolder::addSpriteString("highScore", new SpriteString( highScore , WIN_WIDTH/2 - (int) (highScore.size()*6), 30) );
    SpriteStringHolder::addSpriteString("remainingLoops", new SpriteString(remainingLoopsString, WIN_WIDTH - superAce->getSuperAceLoops()*12 -5, WIN_HEIGHT - 15) );
    SpriteStringHolder::addSpriteString("remainingLives", new SpriteString(remainingLivesString, /*WIN_WIDTH - superAce->getSuperAceLives()*12*/ 5, WIN_HEIGHT - 15) );
    SpriteStringHolder::getSpriteString("remainingLoops")->setVisibility(true);
    SpriteStringHolder::addSpriteString("startingReadyLogo", new SpriteString("READY", (WIN_WIDTH / 2)-40, WIN_HEIGHT / 2) );
    SpriteStringHolder::addSpriteString("startingPlayerLogo", new SpriteString("PLAYER", (WIN_WIDTH / 2)-40, (WIN_HEIGHT / 2)+20) );
    SpriteStringHolder::addSpriteString("numberOne", new SpriteString("1", (WIN_WIDTH / 2)+32, (WIN_HEIGHT / 2)+20) );

    SpriteStringHolder::addSpriteString("exit", new SpriteString("EXIT", (WIN_WIDTH / 2 -(5*6)), (WIN_HEIGHT / 2 - 20) ) );
    SpriteStringHolder::getSpriteString("exit")->setVisibility(false);
    SpriteStringHolder::addSpriteString("pause", new SpriteString("RESUME", (WIN_WIDTH / 2 -(5*6)), (WIN_HEIGHT / 2) ) );
    SpriteStringHolder::getSpriteString("pause")->setVisibility(false);
    
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

