

#ifndef Game_hpp
#define Game_hpp
#define FRAME_VALUES 10
#define FPS_INTERVAL 1.0 //seconds.

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
#include <SDL_mixer.h>

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
    
    static Uint32 _fps_lasttime; //the last recorded time.
    static Uint32 _fps_current; //the current FPS.
    static Uint32 _fps_frames; //frames passed since the last recorded fps.
    
    static SDL_Window * _window;
    static SDL_Renderer * _renderer;
	static SDL_Event e;
    
    static GameState _gameState;

	//animation variables
	static unsigned long _currTime ;
    static SpriteString* _fps_sprite;
	
    //SpriteStrings
	static SpriteString* _remaining_loops;
	static unsigned _remaining_loops_num ;
    static float _spriteSize;
    static int _highScore;
    static int _score;
    static SpriteString* _highScoreSprite;
    static SpriteString* _scoreSprite;
	//spriteStrings for Start
	static SpriteString* _startingReadyLogo;
	static SpriteString* _startingPlayerLogo;
	static SpriteString* _numberOne;
	//spriteStrings for End
	static SpriteString* _shootingText;
	static SpriteString* _shootingDownText;
	static SpriteString* _shootingDownPercent;
	static SpriteString* _endingBonusText;
	static SpriteString* _pointsText;
	static SpriteString* _pointsNumber;
	static SpriteString* _letterR;
	static SpriteString* _equals;

    //controller
	static SDL_GameController *_controller;

    static SpriteString* _pause;

	//music
	static Mix_Chunk	*_gunShot;

public:
    
    //basic functions
    static int OnExecute();
    
    static bool OnInit();
    
    static void OnEvent(SDL_Event* e);
    static void LoadGameInfo (const std::string& cataloge);
    static void OnLoop();

    static void OnRender();
    
    static void OnCleanup();


    static bool InitWindow();
    static bool InitRenderer();
    static bool InitData();
    static bool InitBackground();
    static bool InitGameInfo();
	static void InitSuperAceAnimator();
	static void InitGamePad();
	static void InitSounds();
    //get
    static SDL_Window * getWindow();
    static SDL_Renderer * getRenderer();
    static SDL_Surface * getSurface();
    static SDL_Texture * getTexture();
    static GameState getState();
    static unsigned long getGameTime();
    static int getHighScore(void)  ;
    static float getSpriteSize(void)  ;
    static int getScore(void)  ;
    static SpriteString* getHighScoreSprite(void) ;
    static SpriteString* getScoreSprite(void) ;
    
    //updates
    static void updateHighScoreSprite();
    static void updateScoreSprite();
    
    //set
    static void setState(GameState gameState);
    static void setScore(int s);
    static void setSpriteSize(float s);
    static void setHighScore(int s);

    //boolean
    static bool isExit();
    static bool isMainMenu();

	//fps functions
    static void fpsLoop();
	static void fpsThink();
	static void fpsInit();

    //animation functions
    static void setGameTime();

};

#endif /* Game_hpp */