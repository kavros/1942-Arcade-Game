

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
#include "SpriteStringHolder.hpp"
#include "SoundHolder.hpp"

//sprites
#include "SpriteAlphaNum.hpp"
#include "SuperAce.h"
#include "Background.hpp"
#include "PowerUp.hpp"

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
	EXIT,
    GAME_OVER,
	END_OF_STAGE
};

class Game{
    
private:
    
    static Uint32 _fps_lasttime; //the last recorded time.
    static Uint32 _fps_current; //the current FPS.
    static Uint32 _fps_frames; //frames passed since the last recorded fps.
    
    static SDL_Window * _window;
    static SDL_Renderer * _renderer;
	static SDL_Event event;
    static SDL_Event prevEvent;

    static GameState _gameState;
    static std::list<unsigned> _powerUpsOfStage;
    //Game Variables
	static unsigned long _currTime ;
	//static unsigned _remaining_loops_num ;
    static float _spriteSize;
    static int _highScore;
    static int _score;
    static bool _mute;
    //controller
	static SDL_GameController *_controller;

public:
    
    //basic functions
    static int OnExecute();
    
    static bool OnInit();
    
    static void singleplayerGameOnEvent();
    static void multiplayerGameOnEvent();
    static void OnEvent();
    static void pauseManager();
    static void gameOver();
    static void LoadGameInfo (const std::string& cataloge);
    
    static void destructionManagerOnLoop();
    static void GameOnLoop();
    static void OnLoop();

    static void InitGame();
    static void OnRender();
    
    static void cleanUpHolders();
    static void OnCleanup();


    static bool InitWindow();
    static bool InitRenderer();
    static bool InitData();
    static bool InitGameInfo();

	//static void InitSuperAceAnimator();

	static void InitGamePad();
    
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
    static unsigned getNextPowerUpType();
    //static int getRemainingLoops(void);
    
    //updates
    static void updateHighScoreJson(const std::string& cataloge);
    static void updateHighScoreSprite();
    static void updateScoreSprite();

	static void UpdateAllGrayPlaneAnimations();

    //set
    static void setState(GameState gameState);
    static void setScore(int s);
    static void setSpriteSize(float s);
    static void setHighScore(int s);
    static void setNextPowerUpType(unsigned);
    //static void setRemainingLoops(int loops);

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