#include "Game.hpp"
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
bool Game::OnInit(){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}
	
	for (int i = 0; i < SDL_NumJoysticks(); ++i){
		if (SDL_IsGameController(i)){

			_controller = SDL_GameControllerOpen(i);
			std::cout << SDL_GameControllerMapping(_controller) << endl;
			break;
		}
	}
	//std::cout << SDL_GameControllerAddMapping("0,X360 Controller, a:b6,b:b10");
    InitWindow();
	
    InitRenderer();

    InitData();
    LoadGameInfo("config.json");
    
    InitMainMenuSinglePlayer();
    InitMainMenuMultiPlayer();

    InitBackground();

    InitSuperAce();

    InitGameInfo();
    
	InitSuperAceAnimator();
	
    return true;
}

void Game::InitSuperAceAnimator(){
    

    animid_t id = "SuperAceAnimation";
    
    Sprite* superAce = SpritesHolder::getSpritesHolder()->getSprites(SUPER_ACE)->front();
	
	MovingPathAnimation* superAceStartingAnimation =
		(MovingPathAnimation*)AnimationHolder::getAnimationHolder()->getAnimation("superAceStartingAnimation");
	MovingPathAnimator* superAceStartingAnimator  =	new MovingPathAnimator(
		"SuperAceStartingAnimator", superAce, superAceStartingAnimation
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


	AnimatorHolder::getAnimatorHolder()->Register(superAceMovingAnimator);
	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorUp);
	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorRight);
	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorRightRight);
	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorDown);
	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorLeft);
	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorLeftLeft);
	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorManeuever);
	AnimatorHolder::getAnimatorHolder()->Register(superAceStartingAnimator);



	 

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

bool Game::InitMainMenuSinglePlayer(){
    /*static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;
    
    SDL_Rect dstRect;
    dstRect.x=0;
    dstRect.y=0;
    dstRect.w=WIN_WIDTH;
    dstRect.h=WIN_HEIGHT;
    
    bool _isVisible=true;
    SpriteType _type=MAIN_MENU_SINGLEPLAYER;
    
    AnimationFilm* animationFilm = AnimationFilmHolder::Get()->GetFilm("mainMenuSingleplayer") ;
 
    Sprite *sprite=new Sprite(dstRect,_isVisible,_type,animationFilm);
    
    SpritesHolder::getSpritesHolder()->add(sprite);*/
    
    return true;
}

bool Game::InitMainMenuMultiPlayer(){
    /*static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;
    
    SDL_Rect dstRect;
    dstRect.x=0;
    dstRect.y=0;
    dstRect.w=WIN_WIDTH;
    dstRect.h=WIN_HEIGHT;
    
    bool _isVisible=true;
    SpriteType _type=MAIN_MENU_MULTIPLAYER;
    
    AnimationFilm* animationFilm = AnimationFilmHolder::Get()->GetFilm("mainMenuMultiplayer") ;
    
    Sprite *sprite=new Sprite(dstRect,_isVisible,_type,animationFilm);
    
    SpritesHolder::getSpritesHolder()->add(sprite);*/
    
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

bool Game::InitSuperAce(){
    
    //SpritesHolder::getSpritesHolder()->add(new SuperAce());
    
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
    
    
    Document document;
    document.Parse(data);
    assert(document.IsObject());
    _remaining_loops_num =document["superAceLoops"].GetInt();
}

bool Game::InitGameInfo(){
    static int unique = 0;
    if(unique >1){
        assert(0);
    }
    unique++;
    
    //SpriteAlphaNum* three = new SpriteAlphaNum('3',0,0);
    /*SpriteString* thirtythree = */
    new SpriteString("SCORE",20,10);
    new SpriteString("00000",20,24);
    new SpriteString("HIGH",200,10);
    new SpriteString("SCORE",250,10);
    new SpriteString("FPS",450,10);

    _fps_sprite				 = new SpriteString("0000",450,24);
    std::string str = "";
    for(int i = 0; i<  _remaining_loops_num; i++){
       str += "R";
    }
	_remaining_loops		 = new SpriteString(str, WIN_WIDTH - _remaining_loops_num*12, WIN_HEIGHT - 12);
	_startingReadyLogo		 = new SpriteString("READY", (WIN_WIDTH / 2)-40, WIN_HEIGHT / 2);
	_startingPlayerLogo		 = new SpriteString("PLAYER", (WIN_WIDTH / 2)-40, (WIN_HEIGHT / 2)+20);
	_numberOne				 = new SpriteString("1", (WIN_WIDTH / 2)+30, (WIN_HEIGHT / 2)+20);
	_pause					 = new SpriteString("PAUSE", (WIN_WIDTH / 2), (WIN_HEIGHT / 2));
	
	for (int i = 0; i < 5; ++i){
		_pause->getSpriteAlphaNum(i)->setVisibility(false);
		_pause->getSpriteAlphaNum(i)->setAlive(true);
		_startingReadyLogo->getSpriteAlphaNum(i)->setAlive(true);
		_startingPlayerLogo->getSpriteAlphaNum(i)->setAlive(true);
	}
	_startingPlayerLogo->getSpriteAlphaNum(5)->setAlive(true);
	_numberOne->getSpriteAlphaNum(0)->setAlive(true);

    //SpritesHolder::getSpritesHolder()->add(three);
    return true;
}

