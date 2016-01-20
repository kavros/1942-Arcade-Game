

#ifndef Game_hpp
#define Game_hpp
#define FRAME_VALUES 10


#include "includes.h"
//holders
#include "AnimationFilmHolder.hpp"
#include "AnimationHolder.h"
#include "SpritesHolder.hpp"
#include "CollisionChecker.hpp"

//sprites
#include "SpriteAlphaNum.hpp"
#include "SpriteString.hpp"
#include "SuperAce.h"
#include "Background.hpp"

//Animators
#include "MovingAnimator.h"
#include "AnimatorHolder.h"
#include "MovingPathAnimator.h"


enum GameState {
	SINGLEPLAYER_MENU,
	MULTIPLAYER_MENU,
    SINGLEPLAYER_GAME,
    MULTIPLAYER_GAME,
	PAUSE_MENU,
	EXIT
};

class Game{
    
private:
	/*************************************************************/
				//FRAME RATE VARIABLES//
	// How many frames time values to keep
	// The higher the value the smoother the result is...
	// Don't make it 0 or less :)
    
    #define FPS_INTERVAL 1.0 //seconds.
    
    Uint32 _fps_lasttime = SDL_GetTicks(); //the last recorded time.
    Uint32 _fps_current; //the current FPS.
    Uint32 _fps_frames = 0; //frames passed since the last recorded fps.
	
	/**************************************************************/

    static SDL_Window * _window;
    static SDL_Renderer * _renderer;
    
	SDL_Event e;

    static GameState _gameState;

	//usefull for animation 
	static unsigned long _currTime ;
	void setGameTime(){ _currTime = SDL_GetTicks(); }
    SpriteString* _fps_sprite;
	
	SpriteString* _remaining_loops;
	unsigned _remaining_loops_num = 3;
    static float _spriteSize;
    static int _highScore;
    static int _score;
    static SpriteString* _highScoreSprite;
    static SpriteString* _scoreSprite;
	//spriteStrings for Start
	SpriteString* _startingReadyLogo;
	SpriteString* _startingPlayerLogo;
	SpriteString* _numberOne;
	
	/*
	//spriteStrings for End
	SpriteString* _shootingText;
	SpriteString* _downText;
	SpriteString* _shootingDownPercent;
	SpriteString* _endingBonusText;
	SpriteString* _pointsText;
	SpriteString* _pointsNumber;
	SpriteString* _letterR;
	SpriteString* _equals;
	*/






	SpriteString* _pause;

	
	SDL_GameController *_controller =nullptr;

public:
    Game();
    
    //fps
    void fpsLoop();
    
    //<akatsarakis>
    int OnExecute();
    
    bool OnInit();
    
    void OnEvent(SDL_Event* e);
    void LoadGameInfo (const std::string& cataloge);
    void OnLoop();
    
    void OnRender();
    
    void OnCleanup();

    
    bool InitWindow();
    bool InitRenderer();
    bool InitData();

    bool InitMainMenuSinglePlayer();
    bool InitMainMenuMultiPlayer();
    bool InitBackground();
    bool InitSuperAce();
    bool InitGameInfo();
	void InitSuperAceAnimator();

    //</akatsarakis>
    
    //get
    static SDL_Window * getWindow();
    static SDL_Renderer * getRenderer();
    SDL_Surface * getSurface();
    SDL_Texture * getTexture();
    static GameState getState();
    static unsigned long getGameTime();
    static int getHighScore(void)  ;
    static void setHighScore(int s);
    static float getSpriteSize(void)  ;
    static void setSpriteSize(float s);
    static int getScore(void)  ;
    static void setScore(int s);
    SpriteString* getHighScoreSprite(void) ;
    SpriteString* getScoreSprite(void) ;
    static void updateHighScoreSprite();
    static void updateScoreSprite();
    //set
    static void setState(GameState gameState);

    //boolean
    bool isExit();
    bool isMainMenu();

	//fps functions
	void fpsThink();
	void fpsInit();

};

#endif /* Game_hpp */