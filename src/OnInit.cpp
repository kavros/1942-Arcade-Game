#include "Game.hpp"

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


	MovingPathAnimation* superAceAnimationLeft	= 
		(MovingPathAnimation*) AnimationHolder::getAnimationHolder()->getAnimation("superAceAnimationLeft");
	MovingPathAnimator* superAceAnimatorLeft	= new MovingPathAnimator(
		"SuperAceAnimatorLeft", superAce, superAceAnimationLeft
		);


	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorUp);
	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorRight);
	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorDown);
	AnimatorHolder::getAnimatorHolder()->Register(superAceAnimatorLeft);
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
    _fps_sprite = new SpriteString("0000",450,24);
	_remaining_loops = new SpriteString("RRR", WIN_WIDTH - 36, WIN_HEIGHT - 12);
    //SpritesHolder::getSpritesHolder()->add(three);
    return true;
}

